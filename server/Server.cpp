/*
// Server.cpp for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Tue May  6 11:29:52 2014 buret_j
// Last update Thu Jun  5 16:31:55 2014 buret_j
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
Server::Server::filterCmd()
{
  t_cmd         *cmd = new t_cmd;
  size_t        cur_1 = 0;
  size_t        cur_2 = 0;

  if (this->_messages.size() > 0)
    {
      t_msg		*msg = this->_messages.front();
      cmd->date = msg->_date;
      cur_1 = msg->_msg.find(" ", cur_1);
      this->getInformation(msg->_msg, &cmd->id, cur_2, cur_1);
      cur_2 = msg->_msg.find(" ", cur_1 + 1);
      this->getInformation(msg->_msg, &cmd->pos.first, cur_1 + 1, cur_2 - (cur_1 + 1));
      cur_1 = msg->_msg.find(" ", cur_2 + 1);
      this->getInformation(msg->_msg, &cmd->pos.first, cur_2 + 1, cur_1 - (cur_2 + 1));
      cur_2 = msg->_msg.find(" ", cur_1 + 1);
      cmd->action = msg->_msg.substr(cur_1 + 1, cur_2 - (cur_1 + 1));
      while (cur_2 != std::string::npos && cur_1 != std::string::npos)
	{
	  cur_1 = msg->_msg.find(" ", cur_2 + 1);
	  cmd->params.push_back(msg->_msg.substr(cur_2 + 1, cur_1 - (cur_2 + 1)));
	  if (cur_1 != std::string::npos && (cur_2 = msg->_msg.find(" ", cur_1 + 1)) != std::string::npos)
	    cmd->params.push_back(msg->_msg.substr(cur_1 + 1, cur_2 - (cur_1 + 1)));
	}
      delete this->_messages.front();
      this->putCmdInQueue(cmd);
    }
}

void
Server::Server::putCmdInQueue(t_cmd *cmd)
{
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

Server::t_msg *
Server::Server::filterMsg(const t_cmd &cmd)
{
  t_msg	*msg = new t_msg;
  std::stringstream convert;

  msg->_date = cmd.date;
  convert << cmd.id << " " << cmd.pos.first << " " << cmd.pos.second << " " << cmd.action;
  msg->_msg = convert.str();
  for (std::vector<std::string>::const_iterator it = cmd.params.begin(); it != cmd.params.end(); ++it)
    {
      convert.str(std::string());
      convert.clear();
      convert << " " << *it;
      msg->_msg += convert.str();
    }
  return (msg);
}

/*
** RUNSERVER
*/

// Server::Player		*Server::Server::getPlayer(size_t posx, size_t posy)
// {
//   std::map<std::pair<size_t, size_t>, Player *>::iterator	it;

//   for (it = this->_playersAlive.begin(); it != this->_playersAlive.end(); ++it)
//     {
//       if (posx == it->first.first && posy == it->first.second)
// 	return (it->second);
//     }
//   return (NULL);
// }

// Server::Player		*Server::Server::getPlayer(size_t id)
// {
//   std::map<std::pair<size_t, size_t>, Player *>::iterator	it;

//   for (it = this->_playersAlive.begin(); it != this->_playersAlive.end(); ++it)
//     {
//       if (it->second->getID() == id)
// 	return (it->second);
//     }
//   return (NULL);
// }

// void		Server::Server::movePlayer()
// {
//   std::cout << "move player" << std::endl;
// }

void		Server::Server::createPlayer()
{
  // Player	*_p = new Player(1, NULL, 0);
  // this->_playersAlive[] = ;
}

// void
// Server::Server::addMessage(Socket *s) {
//   Server::t_msg *m = new Server::t_msg;

//   gettimeofday(&m->_date, NULL);
//   s->getline(m->_msg);
//   _messages.push_back(m);
// }

// void
// Server::Server::sendMessage(Socket *s) {
//   t_msgToSend { size_t left; std::string toSnd; }
//   Player { std::list<t_msgToSend *> toSnd; }
//   player.toSnd.pop_front() [ ->left -= 1; s->write(); ]
// }

static void
trampoline(void *p, Socket *s, bool b[3]) {

  if (b[0])
    ;
  (void)p;
  (void)s;
  //   ((Server::Server *)p)->addMessage(s);
  // if (b[1])
  //   ((Server::Server *)p)->sendMessage(s);
  if (b[2])
    ;
  
}

void
Server::Server::run() {

  while (_run && _co->update(0) >= 0) {
    _co->perform(&trampoline, this);
    filterCmd();
    // _game->update();
    // ..
  }

}


// void		Server::Server::run()
// {
//   t_cmd		*_cmd;
//   Player	*_player;
//   std::map<std::string, void (Server::Server::*)()>	_action;
//   t_cmd             _tmp;

//   _action["MOVE"] = &Server::Server::movePlayer;
//   _tmp.id = 1;
//   TIME(_tmp.date);
//   std::pair<size_t, size_t> pos(0, 0);
//   _tmp.pos = pos;
//   _tmp.action.append("MOVE");
//   _tmp.params.push_back("UP");
//   this->_events.push(&_tmp);

//   // while (1)
//   //   {
//   if (this->_events.tryPop(&_cmd) == false)
//     throw ServerException("Nothing in queue");
//   if ((_player = this->getPlayer(_cmd->pos.first, _cmd->pos.second)) == NULL)
//     {
//       if ((_player = this->getPlayer(_cmd->id)) == NULL)
// 	throw ServerException("No player found");
//       _player->setPos(_cmd->pos.first, _cmd->pos.second);
//     }
//   if (_player->getTimeSinceLastCommand() <= (DELAY * _player->getLastCommandMultiplier()
// 					     * _player->getCommandTimeMultiplier()))
//     {
//       (this->*_action[_cmd->action])();
//     }
//   // }
// }
