#include "Server.hpp"

Server::Server::Server(ConnexionHandler *c) : _run(true), _id(1), _co(c) {
  _game = NULL;
  _co->server(4242);
}

Server::Server::Server(ConnexionHandler *c, int p) : _run(true), _id(1), _co(c) {
  _game = NULL;
  _co->server(p);
}

Server::Server::~Server() {
}

/*
**
*/

void
Server::Server::readMessage(Socket *s) {
  std::vector<std::string *> v;
  s->getLine(v);
  for (std::vector<std::string *>::iterator it = v.begin(); it != v.end(); ++it) {
    _messages.push_back(*it);
  }
}

void
Server::Server::sendMessage(Socket *s) {
  if (_messenger.hasSomethingToSay(s)) {
    std::string m;
    _messenger.retrieveMessage(s, m);
    s->write(m);
  }
}

void
Server::Server::sendBroadcast() {
  for (std::list<Player *>::iterator it = _peers.begin();
       it != _peers.end(); ++it) {
    this->sendMessage((*it)->getSocket());
  }
}

/*
** RUNSERVER
*/

void
Server::Server::trampoline_performResult(void *p, Socket *s, bool b[3]) {
  if (b[2]) {
    reinterpret_cast<Server::Server *>(p)->peerDisconnected(s);
  }
  else {
    if (b[0]) {
      reinterpret_cast<Server::Server *>(p)->readMessage(s);
    }
  }
}

#define TIMELOOP 200

void
Server::Server::run() {
  int	timeLoop = 0;
  int   ret;

  while (_run && (ret = _co->update(timeLoop)) >= 0) {
    if (_game) {
      if (_game->ended()) {
	delete _game;
	_game = 0;
	ret = 0;
      }
      else
	_game->updateTimeLeft();
    }

    if (ret) {
      _co->perform(&trampoline_performResult, this);
      while (!_messages.empty()) {
	this->filterMsg();
	ret = 0;
      }
      if (!_ext.empty()) {
	ret = 0;
	while (!_ext.empty())
	  ret += (int)this->manageAdminCommand();
      }

      timeLoop = 0;
    }
    else {
      timeLoop = TIMELOOP;
    }
    if (!ret) {
      if (_game && !_game->isStarted()) {
	_game->update();
      }
      else if (!_game || _game->isPaused() || !_game->hasSomethingToDo()) {
	timeLoop = _messenger.hasSomethingToSay() ? 0 : TIMELOOP;
      }
      else {
	_game->update();
	timeLoop = 0;
      }
    }
    this->sendBroadcast();
  } // ! while
}


/*
** EXCEPTION
*/

ServerException::ServerException(const std::string &msg) throw(): ABombermanException(msg) {}
ServerException::~ServerException(void) throw() {}
