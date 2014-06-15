#include "Server.hpp"

Server::Server::Server(ConnexionHandler *c) : _run(true), _id(1), _co(c) {
  _game = NULL;
  _co->server(4242);
}

Server::Server::Server(ConnexionHandler *c, int p) : _run(true), _co(c) {
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
    std::cout << ">> " << **it << std::endl;
  }
}

void
Server::Server::sendMessage(Socket *s) {
  DEBUG("Server::Server::sendMessage()", 1);
  if (_messenger.hasSomethingToSay(s)) {
    std::string m;
    _messenger.retrieveMessage(s, m);
    std::cout << "Server send : [" << m << "]" << std::endl;
    s->write(m);
  }
  DEBUG("!Server::Server::sendMessage()", -1);
}

void
Server::Server::sendBroadcast() {
  DEBUG("Server::Server::sendBroadcast()", 1);
  for (std::list<Player *>::iterator it = _peers.begin();
       it != _peers.end(); ++it) {
    this->sendMessage((*it)->getSocket());
  }
  DEBUG("! Server::Server::sendBroadcast()", -1);
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
      reinterpret_cast<Server::Server *>(p)->readMessage(s); // on est censé ajouter ce msg
    }
    // reinterpret_cast<Server::Server *>(p)->sendMessage(s);
  }
}

#define TIMELOOP 500

void
Server::Server::run() {
  DEBUG("Server::server::run()", 1);
  int	timeLoop = 0;
  int   ret;

  while (_run && (ret = _co->update(timeLoop)) >= 0) {
    DEBUG("Server::server::run() => loop", 0);
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
      DEBUG("Server::server::run() => loop => je dois lire qqc", 0);
      _co->perform(&trampoline_performResult, this);
      while (!_messages.empty()) {
	this->filterMsg();
	ret = 0;
      }
      if (!_ext.empty()) {
	DEBUG("Server::server::run() => loop => j'ai une commande admin a regarder", 0);
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
      DEBUG("Server::server::run() => loop => je regarde si j'update le game", 0);

      if (_game && !_game->isStarted()) {
	DEBUG("Server::server::run() => loop => faut que je demare le jeu un jour", 0);
	_game->update();
      }
      else if (!_game || _game->isPaused() || !_game->hasSomethingToDo()) {
	timeLoop = _messenger.hasSomethingToSay() ? 0 : TIMELOOP;
	DEBUG("Server::server::run() => loop => j'ai rien a faire en fait", 0);
      }
      else {
	DEBUG("Server::server::run() => loop => j'update le game", 0);
	_game->update();
	timeLoop = 0;
      }
    }
    this->sendBroadcast();
    DEBUG("Server::server::run() => ! loop\n", 0);
  } // ! while
  DEBUG("! Server::server::run()", -1);
}


/*
** EXCEPTION
*/

ServerException::ServerException(const std::string &msg) throw(): ABombermanException(msg) {}
ServerException::~ServerException(void) throw() {}
