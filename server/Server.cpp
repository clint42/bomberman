/*
// Server.cpp for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Tue May  6 11:29:52 2014 buret_j
// Last update Tue Jun 10 14:35:05 2014 julie franel
*/

#include "Server.hpp"

Server::Server::Server(ConnexionHandler *c) : _run(true), _co(c) {
  _game = NULL;
  _co->server(4242);
}

Server::Server::~Server() {
}

/*
** FILTER
*/

void
Server::Server::getInformation(const std::string *msg, size_t *field, size_t cur_1, size_t cur_2)
{
  if (cur_1 != std::string::npos && cur_2 != std::string::npos)
    {
      std::stringstream convert(msg->substr(cur_1, cur_2));
      convert >> *field;
    }
  else
    field = 0;
}

void
Server::Server::filterMsg() {
  t_cmd *	cmd = new t_cmd;
  size_t        cur_1 = 0;
  size_t        cur_2 = 0;

  if (this->_messages.size() > 0)
    {
      std::string *msg = this->_messages.front();
      if (_game)
	cmd->date = _game->timeLeft();
      cur_1 = msg->find(" ", cur_1);
      this->getInformation(msg, &cmd->id, cur_2, cur_1);
      cur_2 = msg->find(" ", cur_1 + 1);
      this->getInformation(msg, &cmd->pos.first, cur_1 + 1, cur_2 - (cur_1 + 1));
      cur_1 = msg->find(" ", cur_2 + 1);
      this->getInformation(msg, &cmd->pos.first, cur_2 + 1, cur_1 - (cur_2 + 1));
      cur_2 = msg->find(" ", cur_1 + 1);
      cmd->action = msg->substr(cur_1 + 1, cur_2 - (cur_1 + 1));
      while (cur_2 != std::string::npos && cur_1 != std::string::npos) {
	cur_1 = msg->find(" ", cur_2 + 1);
	cmd->params.push_back(msg->substr(cur_2 + 1, cur_1 - (cur_2 + 1)));
	if (cur_1 != std::string::npos && (cur_2 = msg->find(" ", cur_1 + 1)) != std::string::npos)
	  cmd->params.push_back(msg->substr(cur_1 + 1, cur_2 - (cur_1 + 1)));
      }
      _messages.pop_front();
      delete msg;
      this->putCmdInQueue(cmd);
    }
}

void
Server::Server::putCmdInQueue(t_cmd *cmd)
{
  if (this->_game && cmd->params.size() == 1 &&
      (cmd->action.compare("BOMB") || (cmd->action.compare("MOVE") == 0 &&
       (cmd->params[0].compare("UP") == 0 ||
	cmd->params[0].compare("DOWN") == 0 ||
	cmd->params[0].compare("LEFT") == 0 ||
	cmd->params[0].compare("RIGHT") == 0))))
    this->_game->addEvent(cmd);
  else if (((cmd->action.compare("PAUSE") ||
	     cmd->action.compare("KILL")) && cmd->params.size() == 0) ||
	   (cmd->action.compare("CONFIG") && cmd->params.size() == 3))
    this->_ext.push_back(cmd);
  else
    delete cmd;
}

/*
** RUNSERVER
*/

void
Server::Server::addPeer(Socket *s) {
  static size_t id = 1;
  Player *p = new Player(id, s);
  std::string welcome;

  _peers.push_back(p);
  CVRT_SIZET_TO_STRING(welcome, id);
  welcome += " 0 0 WELCOME";
  _messenger.addMessage(s, welcome);
  ++id;
}

void
Server::Server::addMessage(Socket *s) {
  std::string *m = new std::string;
  s->getLine(*m);
  _messages.push_back(m);
}

void
Server::Server::sendMessage(Socket *s) {
  std::string m;
  _messenger.retrieveMessage(s, m);
  s->write(m);
}

void
Server::Server::peerDisconnected(Socket *s) {
  int occurences = 0;
  for (std::list<Player *>::iterator it = _peers.begin();
       occurences != 2 && it != _peers.end(); ++it) {
    if ((*it)->getSocket() == s) {
      if (_game)
	_game->killPlayer(*it);
      it = _peers.erase(it);
      --it;
      ++occurences;
    }
  }
  _co->rmSocket(s);
}

static void // make it a Server::Server static class methode
trampoline(void *p, Socket *s, bool b[3]) {
  if (b[2]) {
    // DEBUG("trampoline() => socket closed", 1);
    reinterpret_cast<Server::Server *>(p)->peerDisconnected(s);
  }
  else {
    if (b[0]) {
      // DEBUG("trampoline() => socket autorise a lire dessus", 0);
      reinterpret_cast<Server::Server *>(p)->addMessage(s);
    }
    if (b[1]) {
      // DEBUG("trampoline() => socket autorise a ecrire dessus", 0);
      reinterpret_cast<Server::Server *>(p)->sendMessage(s);
    }
  }
}

bool Server::Game::_isInit = false;
std::map<std::string, Server::Game::Type> Server::Game::_types;

bool		Server::Server::funcWelcome(const t_cmd *_cmd)
{
  if (Game::_isInit == false)
    {
      Game::_isInit = true;
      Game::_types["LAST_MAN_STANDING"] = Game::LAST_MAN_STANDING;
      Game::_types["FREE_FOR_ALL"] = Game::FREE_FOR_ALL;
      Game::_types["TEAM_DEATH_MATCH"] = Game::TEAM_DEATH_MATCH;
      Game::_types["TEAM_SURVIVOR"] = Game::TEAM_SURVIVOR;
    }

  try
    {
      size_t	p;
      size_t	b;
      size_t	t;

      CVRT_STRING_TO_SIZET(_cmd->params[1], p);
      CVRT_STRING_TO_SIZET(_cmd->params[2], b);
      CVRT_STRING_TO_SIZET(_cmd->params[3], t);
      this->_game = new Game(_cmd->params[0], p, b, t, Game::_types[_cmd->params[4]], this->_peers, &this->_messenger);
      return (true);
    }
  catch (GameException e)
    {
      std::cerr << e.what() << std::endl;
      return (false);
    }
}

bool	Server::Server::funcPause(__attribute__((unused))const t_cmd *_cmd)
{
  if (this->_game->isPaused() == true)
    this->_game->start();
  else
    this->_game->pause();
  return (true);
}

bool	Server::Server::funcKill(__attribute__((unused))const t_cmd *_cmd)
{
  this->_run = false;
  return (true);
}

bool Server::Server::_isInit = false;
std::map<std::string, bool (Server::Server::*)(const Server::t_cmd *)> Server::Server::_func;

bool
Server::Server::manageAdminCommand()
{
  if (Server::_isInit == false)
    {
      Server::_isInit = true;
      Server::_func["CONFIG"] = &Server::Server::funcWelcome;
      Server::_func["PAUSE"] = &Server::Server::funcPause;
      Server::_func["KILL"] = &Server::Server::funcKill;
    }
  bool ret = false;

  if (this->_ext.front()->id == 1)
    ret = (this->*_func[this->_ext.front()->action])(this->_ext.front());
  this->_ext.pop_front();
  return ret;
}

void	Server::Server::watchEvent(int e)
{
  std::list<Player *>::iterator	it;

  for (it = _peers.begin(); it != _peers.end(); ++it)
    {
      this->_co->watchEventOnSocket((*it)->getSocket(), e);
    }
}

void	Server::Server::unwatchEvent(int e)
{
  std::list<Player *>::iterator	it;

  for (it = _peers.begin(); it != _peers.end(); ++it)
    {
      this->_co->unwatchEventOnSocket((*it)->getSocket(), e);
    }
}

void
Server::Server::run() {
  // DEBUG("Server::server::run()", 1);
  size_t timeLoop = 0;
  while (_run && _co->update(timeLoop) >= 0) {
    _co->perform(&trampoline, this);
    filterMsg();
    if (!(_ext.size() && manageAdminCommand()) && _game && !_game->isPaused())
      {
      _game->update();
      std::cout << "UPDATE" << std::endl;
      }
    else if (!_game || !_game->hasSomethingToDo())
      timeLoop = 7000;
    else
      timeLoop = 0;
  }
  // DEBUG("! Server::server::run()", -1);
}
