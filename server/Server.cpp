/*
// Server.cpp for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Tue May  6 11:29:52 2014 buret_j
// Last update Sat Jun  7 19:04:13 2014 buret_j
*/

#include "Server.hpp"

Server::Server::Server(ConnexionHandler *c) : _run(true), _co(c) {
  _game = NULL;
  _co->server(4242);
}

Server::Server::~Server() {
}

// void
// Server::Server::isDead(size_t id, std::pair<size_t, size_t> pos)
// {
//   std::map<std::pair<size_t, size_t>, Player *>::iterator it;

//   it = this->_playersAlive.find(pos);
//   if (it != this->_playersAlive.end() && it->second->getID() == id)
//     {
//       this->_playersDead.insert(std::pair<std::pair<size_t, size_t>, Player *>(it->first, it->second));
//       this->_playersAlive.erase(it);
//     }
// }

// void
// Server::Server::allDead()
// {
//   std::map<std::pair<size_t, size_t>, Player *>::iterator it;
//   size_t        len;

//   len = this->_playersAlive.size();
//   while (len > 0)
//     {
//       it = this->_playersAlive.begin();
//       this->_playersDead.insert(std::pair<std::pair<size_t, size_t>, Player *>(it->first, it->second));
//       this->_playersAlive.erase(it);
//       --len;
//     }
// }

// void
// Server::Server::putInPlayersAlive()
// {
//   size_t        maxPlayer;
//   size_t        countAlive;
//   size_t        countDead;
//   std::map<std::pair<size_t, size_t>, Player *>::iterator it;

//   maxPlayer = this->_map->getNbrSlot();
//   countAlive = this->_playersAlive.size();
//   countDead = this->_playersDead.size();

//   while (countAlive < maxPlayer && countDead > 0)
//     {
//       it = this->_playersDead.begin();
//       this->_playersAlive.insert(std::pair<std::pair<size_t, size_t>, Player *> (it->first, it->second));
//       this->_playersDead.erase(it);
//       ++countAlive;
//       --countDead;
//     }
// }

/*
** FILTER
*/

void
Server::Server::getInformation(const std::string &msg, size_t *field, size_t cur_1, size_t cur_2)
{
  if (cur_1 != std::string::npos && cur_2 != std::string::npos)
    {
      std::stringstream convert(msg.substr(cur_1, cur_2));
      convert >> *field;
    }
  else
    field = 0;
}

void
Server::Server::filterCmd() { // je te laisse virer tous les msg->_msg etc :)
  t_cmd *	cmd = new t_cmd;
  size_t        cur_1 = 0;
  size_t        cur_2 = 0;

  if (this->_messages.size() > 0)
    {
      std::string *msg = this->_messages.front();
      if (_game)
	cmd->date = _game->timeLeft();
      cur_1 = msg->_msg.find(" ", cur_1);
      this->getInformation(msg->_msg, &cmd->id, cur_2, cur_1);
      cur_2 = msg->_msg.find(" ", cur_1 + 1);
      this->getInformation(msg->_msg, &cmd->pos.first, cur_1 + 1, cur_2 - (cur_1 + 1));
      cur_1 = msg->_msg.find(" ", cur_2 + 1);
      this->getInformation(msg->_msg, &cmd->pos.first, cur_2 + 1, cur_1 - (cur_2 + 1));
      cur_2 = msg->_msg.find(" ", cur_1 + 1);
      cmd->action = msg->_msg.substr(cur_1 + 1, cur_2 - (cur_1 + 1));
      while (cur_2 != std::string::npos && cur_1 != std::string::npos) {
	cur_1 = msg->_msg.find(" ", cur_2 + 1);
	cmd->params.push_back(msg->_msg.substr(cur_2 + 1, cur_1 - (cur_2 + 1)));
	if (cur_1 != std::string::npos && (cur_2 = msg->_msg.find(" ", cur_1 + 1)) != std::string::npos)
	  cmd->params.push_back(msg->_msg.substr(cur_1 + 1, cur_2 - (cur_1 + 1)));
      }
      _messages.pop_front();
      delete msg;
      this->putCmdInQueue(cmd);
    }
}

void
Server::Server::putCmdInQueue(t_cmd *cmd)
{ // sert à rien de regarder plus loin si on trouve MOVE ou BOMB et que !date
  // enfin débrouille toi
  // pense juste a pas push (mais qu'en mm delete) le t_cmd* si on en fait rien
  if (cmd->action.compare("MOVE") == 0 &&
      cmd->params.size() == 1 &&
      (cmd->params[0].compare("UP") == 0 ||
       cmd->params[0].compare("DOWN") == 0 ||
       cmd->params[0].compare("LEFT") == 0 ||
       cmd->params[0].compare("RIGHT") == 0))
    this->_game->addEvent(cmd);
  else if (cmd->action.compare("BOMB") == 0 &&
	   cmd->params.size() == 1)
    this->_game->addBomb(cmd);
  else if ((cmd->action.compare("PAUSE") && cmd->params.size() == 0) ||
	   (cmd->action.compare("CONFIG") && cmd->params.size() == 3))
    this->_ext.push(cmd);
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
  welcome += "0 0 WELCOME";
  _messenger.addMessage(s, welcome);
  ++id;
}

void
Server::Server::addMessage(Socket *s) {
  std::string *m = new std::string;
  s->getline(m);
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
  for (int occurences = 0; std::list<Player *>::iterator it = _peers.begin();
       occurences != 2, it != _peers.end(); ++it) {
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

static void
trampoline(void *p, Socket *s, bool b[3]) {
  if (b[0])
    ((Server::Server *)p)->addMessage(s);
  if (b[1])
    ((Server::Server *)p)->sendMessage(s);
  if (b[2])
    ((Server::Server *)p)->peerDisconnected(s);
}

void
Server::Server::manageAdminCommand()
{
  std::map<std::string, func_admin> func;
  func["PAUSE"] = &funcPause;
  func["CONFIG"] = &funcWelcome;
  func["KILL"] = &funcKill;

  if (this->_ext.front()->id == 1)
    func[this->_ext.front()->action]();
  this->_ext.pop_front();
}

void
Server::Server::run() {
  while (_run && _co->update(0) >= 0) {
    _co->perform(&trampoline, this, &_messenger);
    filterCmd();
    if (!(_ext.size() && manageAdmin()) && _game && !_game->isPaused())
      _game->update();
  }
}
