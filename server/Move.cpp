/*
// Server.cpp for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Tue May  6 11:29:52 2014 buret_j
// Last update Thu Jun  5 14:19:03 2014 julie franel
*/

#include "Server.hpp"


// Player      *getPlayer(const size_t, const size_t);
// Player      *getPlayer(const size_t id);

// void        movePlayer(const t_cmd &cmd);
// void        createPlayer();
// std::pair<size_t, size_t>   generatePos(const size_t, const size_t);
// std::pair<size_t, size_t>   newPosUp(const size_t, const size_t);
// std::pair<size_t, size_t>   newPosDown(const size_t, const size_t);
// std::pair<size_t, size_t>   newPosRight(const size_t, const size_t);
// std::pair<size_t, size_t>   newPosLeft(const size_t, const size_t);
// void	run();


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
