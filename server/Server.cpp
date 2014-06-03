/*
// Server.cpp for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Tue May  6 11:29:52 2014 buret_j
// Last update Tue Jun  3 18:23:17 2014 julie franel
*/

#include "Server.hpp"

Server::Server::Server() {
  this->retrieveMapNames();
}

Server::Server::~Server() {
}

size_t
Server::Server::retrieveMapNames() {
  // opens `mapcycle.cfg' and fill _mapNames attribute.
  // ?? should it collect game infos specified for each map too ??
  return (0);
}

void
Server::Server::isDead(size_t id, std::pair<size_t, size_t> pos)
{
  std::map<std::pair<size_t, size_t>, Player *>::iterator it;

  it = this->_playersAlive.find(pos);
  if (it != this->_playersAlive.end() && it->second->getID() == id)
    {
      this->_playersDead.insert(std::pair<std::pair<size_t, size_t>, Player *>(it->first, it->second));
      this->_playersAlive.erase(it);
    }
}

void
Server::Server::allDead()
{
  std::map<std::pair<size_t, size_t>, Player *>::iterator it;
  size_t        len;

  len = this->_playersAlive.size();
  while (len > 0)
    {
      it = this->_playersAlive.begin();
      this->_playersDead.insert(std::pair<std::pair<size_t, size_t>, Player *>(it->first, it->second));
      this->_playersAlive.erase(it);
      --len;
    }
}

void
Server::Server::putInPlayersAlive()
{
  size_t        maxPlayer;
  size_t        countAlive;
  size_t        countDead;
  std::map<std::pair<size_t, size_t>, Player *>::iterator it;

  maxPlayer = this->_map->getNbrSlot();
  countAlive = this->_playersAlive.size();
  countDead = this->_playersDead.size();

  while (countAlive < maxPlayer && countDead > 0)
    {
      it = this->_playersDead.begin();
      this->_playersAlive.insert(std::pair<std::pair<size_t, size_t>, Player *> (it->first, it->second));
      this->_playersDead.erase(it);
      ++countAlive;
      --countDead;
    }
}

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
Server::Server::filterCmd(const t_msg &msg)
{
  t_cmd         *cmd = new t_cmd;
  size_t        cur_1 = 0;
  size_t        cur_2 = 0;

  cmd->date = msg._date;
  cur_1 = msg._msg.find(" ", cur_1);
  this->getInformation(msg._msg, &cmd->id, cur_2, cur_1);
  cur_2 = msg._msg.find(" ", cur_1 + 1);
  this->getInformation(msg._msg, &cmd->pos.first, cur_1 + 1, cur_2 - (cur_1 + 1));
  cur_1 = msg._msg.find(" ", cur_2 + 1);
  this->getInformation(msg._msg, &cmd->pos.first, cur_2 + 1, cur_1 - (cur_2 + 1));
  cur_2 = msg._msg.find(" ", cur_1 + 1);
  cmd->action = msg._msg.substr(cur_1 + 1, cur_2 - (cur_1 + 1));
  while (cur_2 != std::string::npos && cur_1 != std::string::npos)
    {
      cur_1 = msg._msg.find(" ", cur_2 + 1);
      cmd->params.push_back(msg._msg.substr(cur_2 + 1, cur_1 - (cur_2 + 1)));
      if (cur_1 != std::string::npos && (cur_2 = msg._msg.find(" ", cur_1 + 1)) != std::string::npos)
        cmd->params.push_back(msg._msg.substr(cur_1 + 1, cur_2 - (cur_1 + 1)));
    }
  this->putCmdInQueue(cmd);
}

void
Server::Server::putCmdInQueue(t_cmd *cmd)
{
  if (cmd->action.compare("MOVE") == 0 &&
      cmd->params.size() == 1 &&
      (cmd->params[0].compare("UP") == 0 ||
       cmd->params[0].compare("DOWN") == 0 ||
       cmd->params[0].compare("LEFT") == 0 ||
       cmd->params[0].compare("RIGHt") == 0))
    this->_events.push(cmd);
  else if (cmd->action.compare("BOMB") == 0 &&
	   cmd->params.size() == 1)
    this->_bomb.push(cmd);
  else if ((cmd->action.compare("PAUSE") && cmd->params.size() == 0) ||
	   (cmd->action.compare("CONNECT") && cmd->params.size() == 3))
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

Server::Player		*Server::Server::getPlayer(const size_t posx, const size_t posy)
{
  std::map<std::pair<size_t, size_t>, Player *>::iterator	it;

  for (it = this->_playersAlive.begin(); it != this->_playersAlive.end(); ++it)
    {
      if (posx == it->first.first && posy == it->first.second)
	return (it->second);
    }
  return (NULL);
}

Server::Player		*Server::Server::getPlayer(const size_t id)
{
  std::map<std::pair<size_t, size_t>, Player *>::iterator	it;

  for (it = this->_playersAlive.begin(); it != this->_playersAlive.end(); ++it)
    {
      if (it->second->getID() == id)
	return (it->second);
    }
  return (NULL);
}

std::pair<size_t, size_t>	Server::Server::newPosUp(const size_t posx, const size_t posy)
{
  std::pair<size_t, size_t> pos;

  pos.first = posx;
  pos.second = posy - 1;
  return (pos);
}

std::pair<size_t, size_t>	Server::Server::newPosLeft(const size_t posx, const size_t posy)
{
  std::pair<size_t, size_t> pos;

  pos.first = posx - 1;
  pos.second = posy;
  return (pos);
}

std::pair<size_t, size_t>	Server::Server::newPosDown(const size_t posx, const size_t posy)
{
  std::pair<size_t, size_t> pos;

  if ((posy + 1) < this->_map->getHeight())
    {
      pos.first = posx;
      pos.second = posy + 1;
    }
  else
    {
      pos.first = -1;
      pos.second = -1;
    }
  return (pos);
}

std::pair<size_t, size_t>	Server::Server::newPosRight(const size_t posx, const size_t posy)
{
  std::pair<size_t, size_t> pos;

  if ((posx + 1) < this->_map->getWidth())
    {
      pos.first = posx + 1;
      pos.second = posy;
    }
  else
    {
      pos.first = -1;
      pos.second = -1;
    }
  return (pos);
}

void		Server::Server::movePlayer(const t_cmd &cmd)
{
  std::map<std::string, std::pair<size_t, size_t> >	_dir;

  _dir["UP"] = this->newPosUp(cmd.pos.first, cmd.pos.second);
  _dir["DOWN"] = this->newPosDown(cmd.pos.first, cmd.pos.second);
  _dir["LEFT"] = this->newPosLeft(cmd.pos.first, cmd.pos.second);
  _dir["RIGHT"] = this->newPosRight(cmd.pos.first, cmd.pos.second);
  std::cout << *(cmd.params.begin()) << std::endl;
  //  if (this->_map->getElemAtPos())
}

std::pair<size_t, size_t>	Server::Server::generatePos(const size_t posx, const size_t posy)
{
  size_t			_posx;
  size_t			_posy;

  _posx = rand() % this->_map->getWidth();
  _posy = rand() % this->_map->getHeight();
  if ((_posx == posx && _posy == posy) || (this->_map->getElemAtPos(_posx, _posy) != 0))
    return (this->generatePos(_posx, _posy));
  std::pair<size_t, size_t> pos(_posx, _posy);
  return (pos);
}

void		Server::Server::createPlayer()
{
  std::pair<size_t, size_t>	pos = this->generatePos(-1, -1);

  Player	*_p = new Player(1, NULL, 0);
  this->_playersAlive[pos] = _p;
}

void		Server::Server::run()
{
  t_cmd		*_cmd;
  Player	*_player;
  std::map<std::string, void (Server::Server::*)(const t_cmd &)>	_action;
  t_cmd		_tmp;
  Map		*_map = new Map("test.map");

  this->_map = _map;
  _action["MOVE"] = &Server::Server::movePlayer;
  _tmp.id = 1;
  TIME(_tmp.date);
  std::pair<size_t, size_t> pos(0, 0);
  _tmp.pos = pos;
  _tmp.action.append("MOVE");
  _tmp.params.push_back("UP");
  this->_events.push(&_tmp);
  this->createPlayer();

  // while (1)
  //   {
  if (this->_events.tryPop(&_cmd) == false)
    throw ServerException("Nothing in queue");
  if ((_player = this->getPlayer(_cmd->pos.first, _cmd->pos.second)) == NULL)
    {
      if ((_player = this->getPlayer(_cmd->id)) == NULL)
  	throw ServerException("No player found");
      _player->setPos(_cmd->pos.first, _cmd->pos.second);
    }
  // if (_player->getTimeSinceLastCommand() <= (DELAY * _player->getLastCommandMultiplier()
  // 					     * _player->getCommandTimeMultiplier()))
  //   {
  (this->*_action[_cmd->action])(*_cmd);
    // }
  // }
}
