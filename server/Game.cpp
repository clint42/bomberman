/*
// Game.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Fri May 30 16:58:20 2014 buret_j
<<<<<<< HEAD
** Last update Sun Jun  8 20:07:25 2014 lafitt_g
*/

#include "Game.hpp"

static Server::Game::Play g_Plays[] = {
  { 0,  1,  1, 0, false, 0 },
  { 0,  1,  1, 0, false, RESPAWN_DELAY },
  { 4, 16,  1, 0, false, RESPAWN_DELAY },
  { 4, 16, 15, 2,  true, 0 }
};


Server::Game::Game(std::string const &m, size_t p, size_t b, size_t t, Type type,
		   std::list<Player *> const &peers, Messenger *mes) {
  // try {
    _map = new Map(m);
  // } catch MapException {
  //     _map = 0;
  //     throw GameException;
  //   }
  _params = g_Plays[type];
  _started = false;
  _paused = false;
  _time = (Time)t;
  _maxPlayers = p;
  _maxBots = b;
  _round = 0;
  (void)peers;
  _messenger = mes;
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
    if (!_bombs.tryPop(&c)) {
      _bombs.wait();
    } else {
      if (!_bombs.empty())
	_bombs.signal();
      // do
      delete c;
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
    // pause bomb thread (var cond)
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
Server::Game::moveUp(Player *p)
{
  if (p->getPosY() == 0 || this->_map->getElemAtPos(p->getPosX(), p->getPosY()))
    return (false);
  return (p->moveUp());
}

bool
Server::Game::moveRight(Player *p)
{
  if (p->getPosX() == (this->_map->getWidth() - 1) || this->_map->getElemAtPos(p->getPosX(), p->getPosY()))
    return (false);
  return (p->moveRight());
}

bool
Server::Game::moveDown(Player *p)
{
  if (p->getPosY() == (this->_map->getHeight() - 1) || this->_map->getElemAtPos(p->getPosX(), p->getPosY()))
    return (false);
  return (p->moveDown());
}

bool
Server::Game::moveLeft(Player *p)
{
  if (p->getPosX() == 0 || this->_map->getElemAtPos(p->getPosX(), p->getPosY()))
    return (false);
  return (p->moveLeft());
}

bool
Server::Game::orientUp(Player *p)
{
  return(p->orientUp());
}

bool
Server::Game::orientRight(Player *p)
{
  return(p->orientRight());
}

bool
Server::Game::orientDown(Player *p)
{
  return(p->orientDown());
}

bool
Server::Game::orientLeft(Player *p)
{
  return(p->orientLeft());
}

bool
Server::Game::process(Server::t_cmd *c, Player *p)
{
  if (!this->hasDateNextCommandExpired(p))
    return false;

  Server::Player::Action a;
  Server::Player::Dir	 d;
  std::map<std::pair<Server::Player::Action, Server::Player::Dir>,
	   bool (Server::Game::*)(Server::Player *)> func;

  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::MOVE, Server::Player::UP)] = &Server::Game::moveUp;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::MOVE, Server::Player::RIGHT)] = &Server::Game::moveRight;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::MOVE, Server::Player::DOWN)] = &Server::Game::moveDown;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::MOVE, Server::Player::LEFT)] = &Server::Game::moveLeft;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::ORIENT, Server::Player::UP)] = &Server::Game::orientUp;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::ORIENT, Server::Player::RIGHT)] = &Server::Game::orientRight;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::ORIENT, Server::Player::DOWN)] = &Server::Game::orientDown;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::ORIENT, Server::Player::LEFT)] = &Server::Game::orientLeft;

  if (c->action == "MOVE")
      p->getAction(&a, &d, c->params[0]);
  // else if (c->action == "BOMB")
  //   {
  //     a = Server::Player::BOMB;
  //     d = p->getOrientation();
  //   }
  // else if (c->action == "BOMB EXPLOSE")
  //   {
  //     // send directly to messenger
  //   }
  (this->*func[std::pair<Server::Player::Action, Server::Player::Dir>(a, d)])(p);
  
  return (true);
}

void
Server::Game::killPlayer(Player *p) {
  (void)p;
}
