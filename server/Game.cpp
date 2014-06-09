/*
// Game.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Fri May 30 16:58:20 2014 buret_j
** Last update Mon Jun  9 20:16:44 2014 lafitt_g
*/

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
	  if (c->action == "BOMB") c->action += " EXPLOSE";
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
Server::Game::filterCmd(t_cmd const *cmd, std::string &msg) const {
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

/*
** PROCESS
*/

bool
Server::Game::moveUp(Player *p)
{
  if (p->getPosY())
    {
      std::pair<size_t, size_t> pos(p->getPosX(), p->getPosY() - 1);
      std::pair<size_t, size_t> oldPos(p->getPosX(), p->getPosY());
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end())
	{
	  this->_players[pos] = this->_players[oldPos];
	  this->_players.erase(oldPos);
	  return (p->moveUp());
	}
    }
  return false;
}

bool
Server::Game::moveRight(Player *p)
{
  if (p->getPosX() != this->_map->getWidth() - 1)
    {
      std::pair<size_t, size_t> pos(p->getPosX() + 1, p->getPosY());
      std::pair<size_t, size_t> oldPos(p->getPosX(), p->getPosY());
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end())
	{
	  this->_players[pos] = this->_players[oldPos];
	  this->_players.erase(oldPos);
	  return (p->moveRight());
	}
    }
  return false;
}

bool
Server::Game::moveDown(Player *p)
{
  if (p->getPosY() != this->_map->getHeight() - 1)
    {
      std::pair<size_t, size_t> pos(p->getPosX(), p->getPosY() + 1);
      std::pair<size_t, size_t> oldPos(p->getPosX(), p->getPosY());
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end())
	{
	  this->_players[pos] = this->_players[oldPos];
	  this->_players.erase(oldPos);
	  return (p->moveDown());
	}
    }
  return false;
}

bool
Server::Game::moveLeft(Player *p)
{
  if (p->getPosX())
    {
      std::pair<size_t, size_t> pos(p->getPosX() - 1, p->getPosY());
      std::pair<size_t, size_t> oldPos(p->getPosX(), p->getPosY());
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end())
	{
	  this->_players[pos] = this->_players[oldPos];
	  this->_players.erase(oldPos);
	  return (p->moveLeft());
	}
    }
  return false;
}

bool
Server::Game::orientUp(Player *p)
{
  return(p->orient(Server::Player::UP));
}

bool
Server::Game::orientRight(Player *p)
{
  return(p->orient(Server::Player::RIGHT));
}

bool
Server::Game::orientDown(Player *p)
{
  return(p->orient(Server::Player::DOWN));
}

bool
Server::Game::orientLeft(Player *p)
{
  return(p->orient(Server::Player::LEFT));
}

bool
Server::Game::bombUp(Player *p)
{
  if (p->getPosY())
    {
      std::pair<size_t, size_t> pos(p->getPosX(), p->getPosY() - 1);
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end() &&
	  p->getBombsLimit() > p->getBombsOnFloor())
	return (p->dropBomb());
    }
  return false;
}

bool
Server::Game::bombRight(Player *p)
{
  if (p->getPosX() != this->_map->getWidth() - 1)
    {
      std::pair<size_t, size_t> pos(p->getPosX() + 1, p->getPosY());
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end() &&
	  p->getBombsLimit() > p->getBombsOnFloor())
	return (p->dropBomb());
    }
  return false;
}

bool
Server::Game::bombDown(Player *p)
{
  if (p->getPosY() != this->_map->getHeight() - 1)
    {
      std::pair<size_t, size_t> pos(p->getPosX(), p->getPosY() + 1);
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end() &&
	  p->getBombsLimit() > p->getBombsOnFloor())
	return (p->dropBomb());
    }
  return false;
}

bool
Server::Game::bombLeft(Player *p)
{
  if (p->getPosX())
    {
      std::pair<size_t, size_t> pos(p->getPosX() - 1, p->getPosY());
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end() &&
	  p->getBombsLimit() > p->getBombsOnFloor())
	return (p->dropBomb());
    }
  return false;
}

bool Server::Game::_isGame = false;
std::map<std::pair<Server::Player::Action, Server::Player::Dir>,
	 bool (Server::Game::*)(Server::Player *)> Server::Game::func;

bool
Server::Game::process(t_cmd *c, Player *p)
{
  if (!this->hasDateNextCommandExpired(p))
    return false;

  Server::Player::Action a;
  Server::Player::Dir	 d;

  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::MOVE, Server::Player::UP)] = &Server::Game::moveUp;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::MOVE, Server::Player::RIGHT)] = &Server::Game::moveRight;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::MOVE, Server::Player::DOWN)] = &Server::Game::moveDown;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::MOVE, Server::Player::LEFT)] = &Server::Game::moveLeft;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::ORIENT, Server::Player::UP)] = &Server::Game::orientUp;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::ORIENT, Server::Player::RIGHT)] = &Server::Game::orientRight;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::ORIENT, Server::Player::DOWN)] = &Server::Game::orientDown;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::ORIENT, Server::Player::LEFT)] = &Server::Game::orientLeft;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::BOMB, Server::Player::UP)] = &Server::Game::bombUp;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::BOMB, Server::Player::RIGHT)] = &Server::Game::bombRight;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::BOMB, Server::Player::DOWN)] = &Server::Game::bombDown;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::BOMB, Server::Player::LEFT)] = &Server::Game::bombLeft;
  if (c->action == "MOVE")
    {
      p->getAction(&a, &d, c->params[0]);
      if ((this->*func[std::pair<Server::Player::Action, Server::Player::Dir>(a, d)])(p))
	{
	  std::string msg;
	  this->filterCmd(c, msg);
	  this->_messenger->addMessage(p->getSocket(), msg);
	}
    }
  // else if (c->action == "BOMB")
  //   {
  //     a = Server::Player::BOMB;
  //     d = p->getOrientation();
  //     if ((this->*func[std::pair<Server::Player::Action, Server::Player::Dir>(a, d)])(p))
  // 	{
  // 	  t_cmd * cmd = new t_cmd;
  // 	  cmd->id = c->id;
  // 	  cmd->date = c->date;
  // 	  cmd->pos = c->pos;
  // 	  cmd->action = c->action;
  // 	  this->_bombs.push(cmd);
	  
  // 	  std::string msg;
  // 	  this->filterCmd(c, msg);
  // 	  this->_messenger->addMessage(p->getSocket(), msg);
  // 	}
  //   }
  // else if (c->action == "BOMB EXPLOSE")
  //   {
  //     // send directly to messenger
  //   }

  return (true);
}

void
Server::Game::killPlayer(Player *p) {
  (void)p;
}
