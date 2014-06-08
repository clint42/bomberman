//
// Game.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Fri May 30 16:58:20 2014 buret_j
// Last update Sun Jun  8 20:56:07 2014 buret_j
//

#include "Game.hpp"

static Server::Game::Play g_Plays[] = {
  { 0,  1,  1, 0, false, 0 },
  { 0,  1,  1, 0, false, RESPAWN_DELAY },
  { 4, 16,  1, 0, false, RESPAWN_DELAY },
  { 4, 16, 15, 2,  true, 0 }
};


Server::Game::Game(std::string const &m, size_t p, size_t b, size_t t, Type type,
		   std::list<Player *> const &peers, Messenger *mes)
  : _map(0), _params(g_Plays[type]), _time(static_cast<Time>(t)), _messenger(mes),
    _started(false), _paused(false),
    _maxPlayers(p), _maxBots(b), _round(0) {
  (void)_round;
  try {
    _map = new Map(m);
  } catch (MapException) {
      _map = 0;
      throw GameException("Map not found");
    }
    if (_maxPlayers > _map->getNbrSlot()) {
      _maxPlayers = _map->getNbrSlot();
      p = _maxPlayers;
    }
    if (_maxBots + _maxPlayers > _map->getNbrSlot())
      _maxBots = _map->getNbrSlot() - _maxPlayers;
    for (std::list<Player *>::const_iterator it = peers.begin(); p && it != peers.end(); ++it, --p) {
      _players[(*it)->getPos()] = *it;
    }
}

Server::Game::~Game() {
  delete _map;
}

static void *
tramp(void *g) {
  static_cast<Server::Game *>(g)->bombsProcessing();
  return NULL;
}

void
Server::Game::bombsProcessing() {
  t_cmd *	c;

  while (!this->isEnded()) {
    if (_paused || !_bombs.tryPop(&c)) {
      _bombs.wait();
    } else {
      if (!_bombs.empty())
	_bombs.signal();
      { // code
	if (this->timeLeft() - c->date > 0)
	  usleep(this->timeLeft() - c->date);
	if (_paused) {
	  _bombs.push_front(c);
	} else {
	  c->action += " EXPLOSE";
	  _events.push_front(c);
	}
      } // !code
      // delete c; // pas delete puisqu'on repush !! sigsegf autrement...
    }
  }

}

void
Server::Game::start() {
  if (!_started) {
    gettimeofday(&_startedAt, NULL);
    _endAt.tv_usec = _startedAt.tv_usec + (GAME_TIME * _time * 60 * 1000000);
    _endAt.tv_sec = _endAt.tv_usec / 1000000;
    Thread(&tramp, this); // create bombs' thread
    _started = true;
  } else if (_paused) {
    timeval tmp;
    gettimeofday(&tmp, NULL);
    _endAt.tv_usec += tmp.tv_usec - _pausedAt.tv_usec;
    _paused = false;
    _bombs.signal(); // unpause bomb thread (var cond)
  }
}

size_t
Server::Game::timeLeft() const {
  if (!_paused) {
    timeval tmp;
    gettimeofday(&tmp, NULL);
    return _endAt.tv_sec - tmp.tv_sec;
  }
  return _endAt.tv_sec - _pausedAt.tv_sec;
}

void
Server::Game::pause() {
  if (_started && !_paused) {
    gettimeofday(&_pausedAt, NULL);
    _paused = true;
  }
}

void
Server::Game::update() {
  t_cmd *c;
  if (!_events.tryPop(&c))
    return ;

  Player *p = _players[c->pos];
  if (!p || p->getID() != c->id)
    return ;

  if (this->process(c, p)) {
    std::string m;
    this->filterCmd(c, m);
    _messenger->broadcastMessage(m);
  }
}

void
Server::Game::filterCmd(Server::t_cmd const *cmd, std::string &msg) const {
  std::stringstream convert;

  convert << cmd->id << " " << cmd->pos.first << " " << 
    cmd->pos.second << " " << cmd->action;
  msg = convert.str();
  for (std::vector<std::string>::const_iterator it = cmd->params.begin();
       it != cmd->params.end(); ++it) {
    convert.str(std::string());
    convert.clear();
    convert << " " << *it;
    msg += convert.str();
  }
  msg += "\n";
  delete cmd;
}

bool
Server::Game::process(Server::t_cmd *c, Player *p) {
  if (!this->hasDateNextCommandExpired(p))
    return false;

  (void)c;
  return true;
}

void
Server::Game::killPlayer(Player *p) {
  (void)p;
}
