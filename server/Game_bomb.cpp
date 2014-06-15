#include "Game.hpp"

bool
Server::Game::exploseCase(Player *p, const std::pair<size_t, size_t> pos, t_cmd *c)
{
  std::stringstream convert;
  int		ret;
  std::map<std::pair<size_t, size_t>, Player *>::iterator it;

  if ((ret = this->_map->getElemAtPos(pos)))
    {
      if (ret == Map::DWALL || ret == Map::B_BOMB || ret == Map::B_RANGE || ret == Map::B_SPEED)
	{
	  convert << ";0 " << pos.first << " " << pos.second << " DESTROY";
	  c->msg += convert.str();
	  this->createBonus(pos, c, ret);
	}
      if (ret == Map::WALL || ret == Map::DWALL || ret == Map::BOMB || ret == Map::B_BOMB || ret == Map::B_RANGE || ret == Map::B_SPEED)
	return (false);
    }
  else
    {
      if ((it = this->_players.find(pos)) != this->_players.end())
	{
	  convert << ";" << (*it).second->getID() << " " << pos.first << " " << pos.second << " DESTROY";
	  this->killPlayer(pos);
	  p->incrScore();
	}
      convert << ";0 0 0 CREATE FIRE 0 " << pos.first << " " << pos.second;
      c->msg += convert.str();
    }
  return (true);
}

void
Server::Game::bombExplose(Player *p, t_cmd *c)
{
  int		val = 1;
  std::stringstream convert;
  std::pair<size_t, size_t> pos(c->pos.first, c->pos.second);

  // this->_map->setElemAtPos(pos, Map::GROUND);
  p->destroyBomb();
  this->_map->deleteElem(pos);
  convert << "0 " << pos.first << " " << pos.second << " DESTROY";
  convert << ";0 0 0 CREATE FIRE 0 " << pos.first << " " << pos.second;
  c->msg = convert.str();
  // RIGHT
  while (c->pos.first + val < this->_map->getWidth() - 1 && (size_t)val <= p->getBombRange())
    {
      pos.first = c->pos.first + val;
      if (this->exploseCase(p, pos, c) == false)
	break ;
      ++val;
    }
  // LEFT
  val = -1;
  pos.first = c->pos.first;
  while (c->pos.first + val > 0 && (size_t)(val * -1) <= p->getBombRange())
    {
      pos.first = c->pos.first + val;
      if (this->exploseCase(p, pos, c) == false)
	break ;
      --val;
    }
  // UP
  val = -1;
  pos.first = c->pos.first;
  while (c->pos.second + val > 0 && (size_t)(val * -1) <= p->getBombRange())
    {
      pos.second = c->pos.second + val;
      if (this->exploseCase(p, pos, c) == false)
	break ;
      --val;
    }
  // DOWN
  val = 1;
  pos.second = c->pos.second;
  while (c->pos.second + val < this->_map->getHeight() - 1 && (size_t)val <= p->getBombRange())
    {
      pos.second = c->pos.second + val;
      if (this->exploseCase(p, pos, c) == false)
	break ;
      ++val;
    }
  c->msg += "\n";
}

/*
** *****************
*/

bool
Server::Game::bombUp(Player *p, t_cmd *c)
{
  DEBUG("Server::Game::bombUp()", 1);
  if (p->getPosY())
    {
      std::pair<size_t, size_t> pos(p->getPosX(), p->getPosY() - 1);
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end() &&
	  p->getBombsLimit() > p->getBombsOnFloor())
	{
	  std::cout << "Avant bombSwitchQueue" << std::endl;
	  this->bombSwitchQueue(c, pos);
	  std::cout << "Avant buildCmdCreateBomb" << std::endl;
	  this->buildCmdCreateBomb(c, pos);
	  std::cout << "Avant setElemAtPos" << std::endl;
	  this->_map->setElemAtPos(pos, Map::BOMB);
	  DEBUG("Server::Game::bombUp()", 0);
	  return (p->dropBomb());
	}
    }
  DEBUG("Server::Game::bombUp()", -1);
  return false;
}

bool
Server::Game::bombRight(Player *p, t_cmd *c)
{
  if (p->getPosX() != this->_map->getWidth() - 1)
    {
      std::pair<size_t, size_t> pos(p->getPosX() + 1, p->getPosY());
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end() &&
	  p->getBombsLimit() > p->getBombsOnFloor())
	{
	  std::cout << "Avant bombSwitchQueue" << std::endl;
	  this->bombSwitchQueue(c, pos);
	  std::cout << "Avant buildCmdCreateBomb" << std::endl;
	  this->buildCmdCreateBomb(c, pos);
	  std::cout << "Avant setElemAtPos" << std::endl;
	  this->_map->setElemAtPos(pos, Map::BOMB);
	  DEBUG("Server::Game::bombRight()", 0);
	  return (p->dropBomb());
	}
    }
  return false;
}

bool
Server::Game::bombDown(Player *p, t_cmd *c)
{
  if (p->getPosY() != this->_map->getHeight() - 1)
    {
      std::pair<size_t, size_t> pos(p->getPosX(), p->getPosY() + 1);
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end() &&
	  p->getBombsLimit() > p->getBombsOnFloor())
	{
	  std::cout << "Avant bombSwitchQueue" << std::endl;
	  this->bombSwitchQueue(c, pos);
	  std::cout << "Avant buildCmdCreateBomb" << std::endl;
	  this->buildCmdCreateBomb(c, pos);
	  std::cout << "Avant setElemAtPos" << std::endl;
	  this->_map->setElemAtPos(pos, Map::BOMB);
	  DEBUG("Server::Game::bombDown()", 0);
	  return (p->dropBomb());
	}
    }
  return false;
}

bool
Server::Game::bombLeft(Player *p, t_cmd *c)
{
  if (p->getPosX())
    {
      std::pair<size_t, size_t> pos(p->getPosX() - 1, p->getPosY());
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end() &&
	  p->getBombsLimit() > p->getBombsOnFloor())
	{
	  std::cout << "Avant bombSwitchQueue" << std::endl;
	  this->bombSwitchQueue(c, pos);
	  std::cout << "Avant buildCmdCreateBomb" << std::endl;
	  this->buildCmdCreateBomb(c, pos);
	  std::cout << "Avant setElemAtPos" << std::endl;
	  this->_map->setElemAtPos(pos, Map::BOMB);
	  DEBUG("Server::Game::bombLeft()", 0);
	  return (p->dropBomb());
	}
    }
  return false;
}
