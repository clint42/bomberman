//
// Game.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Fri May 30 16:58:20 2014 buret_j
// Last update Sun Jun  8 00:19:43 2014 buret_j
//

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

void
Server::Game::start() {
  if (!_started) {
    gettimeofday(&_startedAt, NULL);
    _endAt.tv_usec = _startedAt.tv_usec + (GAME_TIME * _time * 60 * 1000000);
    _endAt.tv_sec = _endAt.tv_usec / 1000000;
    // create bombs' thread
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
