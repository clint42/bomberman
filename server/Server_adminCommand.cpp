#include "Server.hpp"

bool Server::Game::_isInit = false;
std::map<std::string, Server::Game::Type> Server::Game::_types;

bool
Server::Server::funcWelcome(const t_cmd *_cmd) {
  if (Game::_isInit == false)
    {
      Game::_isInit = true;
      Game::_types["LAST_MAN_STANDING"] = Game::LAST_MAN_STANDING;
      Game::_types["FREE_FOR_ALL"] = Game::FREE_FOR_ALL;
      Game::_types["TEAM_DEATH_MATCH"] = Game::TEAM_DEATH_MATCH;
      Game::_types["TEAM_SURVIVOR"] = Game::TEAM_SURVIVOR;
    }

  DEBUG("Server::Server::funcConfig()", 1);

  try
    {
      size_t	p;
      size_t	b;
      size_t	t;

      CVRT_STRING_TO_SIZET(_cmd->params[1], p);
      CVRT_STRING_TO_SIZET(_cmd->params[2], b);
      CVRT_STRING_TO_SIZET(_cmd->params[3], t);
      this->_game = new Game(_cmd->params[0], p, b, t, Game::_types[_cmd->params[4]],
			     this->_peers, &this->_messenger);
      this->sendBroadcast();
    }
  catch (GameException e)
    {
      std::cerr << e.what() << std::endl;
      _run = false;
      return (false);
    }
  DEBUG("! Server::Server::funcConfig()", -1);
  return (true);
}

bool
Server::Server::funcPause(__attribute__((unused))const t_cmd *_cmd) {
  if (this->_game->isPaused() == true)
    this->_game->start();
  else
    this->_game->pause();
  return (true);
}

Server::Player *
Server::Server::findPeerByID(const size_t id)
{
  (void)id;
  for (std::list<Player *>::iterator it = this->_peers.begin();
       it != this->_peers.end(); ++it) {
    if ((*it)->getID() == id) {
      return *it;
    }
  }
  return 0;
}

bool
Server::Server::funcMd5(t_cmd const *cmd) {
  DEBUG("Server::Server::funcMd5()", 1);

  Player *p;
  p = this->findPeerByID(cmd->id);

  if (!_game || !p || p->hasCertified()) {
    DEBUG("! Server::Server::funcMd5() => player not found", -1);
    return false;
  }
  if (_game->getMapMd5() == cmd->params[0]) {
    DEBUG("Server::Server::funcMd5() => la key match", 0);
    p->hasCertifiedMd5(true);
  }
  else {
    DEBUG("Server::Server::funcMd5() => wrong key. On degage le peer", 0);
    _messenger.addMessage(p->getSocket(), "0 0 0 MAPCORRUPTED");
    this->sendMessage(p->getSocket());
    this->peerDisconnected(p->getSocket());
  }
  DEBUG("! Server::Server::funcMd5()", -1);
  return (true);
}

bool
Server::Server::funcKill(__attribute__((unused))const t_cmd *_cmd) {
  this->_run = false;
  return (true);
}

bool
Server::Server::funcWithFriend(t_cmd const *cmd) {
  Player *p = this->findPeerByID(cmd->id);

  if (p)
    {
      addPeer(p->getSocket());
      return (true);
    }
  return (false);
}

bool Server::Server::_isInit = false;
std::map<std::string, bool (Server::Server::*)(const Server::t_cmd *)> Server::Server::_func;

bool
Server::Server::manageAdminCommand() {
  if (Server::_isInit == false)
    {
      Server::_isInit = true;
      Server::_func["CONFIG"] = &Server::Server::funcWelcome;
	Server::_func["PAUSE"] = &Server::Server::funcPause;
	Server::_func["KILL"] = &Server::Server::funcKill;
	Server::_func["MD5"] = &Server::Server::funcMd5;
	Server::_func["WITHFRIEND"] = &Server::Server::funcWithFriend;
    }
  bool ret = false;

  if (this->_ext.front()->id == 1)
    ret = (this->*_func[this->_ext.front()->action])(this->_ext.front());
  this->_ext.pop_front();
  return ret;
}
