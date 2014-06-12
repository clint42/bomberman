#include "Server.hpp"

void
Server::Server::addPeer(Socket *s) {
  static size_t id = 1;
  Player *p = new Player(id, s);
  std::string welcome;
  std::string s_id;

  _peers.push_back(p);
  CVRT_SIZET_TO_STRING(s_id, id);
  welcome += s_id + " 0 0 WELCOME";
  if (_game) {
    welcome += "\n";
    welcome += s_id;
    welcome += " 0 0 MAP ";
    welcome += _game->getMapName();
  }
  _messenger.addMessage(s, welcome);
  this->sendMessage(s);
  ++id;
}

void
Server::Server::peerDisconnected(Socket *s) {
  int occurences = 0;
  for (std::list<Player *>::iterator it = _peers.begin();
       occurences != 2 && it != _peers.end(); ++it) {
    if ((*it)->getSocket() == s) {
      if (it == _peers.begin())
	_run = false;
      if (_game)
	_game->killPlayer(*it);
      it = _peers.erase(it);
      --it;
      ++occurences;
    }
  }
  _co->rmSocket(s);
}

void
Server::Server::watchEvent(int e) {
  std::list<Player *>::iterator	it;
  
  for (it = _peers.begin(); it != _peers.end(); ++it) {
    this->_co->watchEventOnSocket((*it)->getSocket(), e);
  }
}

void
Server::Server::unwatchEvent(int e) {
  std::list<Player *>::iterator	it;
  
  for (it = _peers.begin(); it != _peers.end(); ++it) {
    this->_co->unwatchEventOnSocket((*it)->getSocket(), e);
  }
}
