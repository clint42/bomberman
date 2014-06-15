#include "Game.hpp"

bool
Server::Game::moveUp(Player *p, t_cmd *c)
{
  (void)c;
  if (p->getPosY())
    {
      std::pair<size_t, size_t> pos(p->getPosX(), p->getPosY() - 1);
      std::pair<size_t, size_t> oldPos(p->getPosX(), p->getPosY());
      int			elem = this->_map->getElemAtPos(pos);

      if (elem == Map::B_BOMB || elem == Map::B_RANGE || elem == Map::B_SPEED)
	this->earnBonus(p, elem, pos);
      if (elem == Map::GROUND && this->_players.find(pos) == this->_players.end())
	{
	  this->_players[pos] = this->_players[oldPos];
	  this->_players.erase(oldPos);
	  p->updateDateNextCommand(Server::Player::MOVE, c->date);
	  return (p->moveUp());
	}
    }
  return false;
}

bool
Server::Game::moveRight(Player *p, t_cmd *c)
{
  (void)c;
  if (p->getPosX() != this->_map->getWidth() - 1)
    {
      std::pair<size_t, size_t> pos(p->getPosX() + 1, p->getPosY());
      std::pair<size_t, size_t> oldPos(p->getPosX(), p->getPosY());
      int			elem = this->_map->getElemAtPos(pos);

      if (elem == Map::B_BOMB || elem == Map::B_RANGE || elem == Map::B_SPEED)
	this->earnBonus(p, elem, pos);
      if (elem == Map::GROUND && this->_players.find(pos) == this->_players.end())
	{
	  this->_players[pos] = this->_players[oldPos];
	  this->_players.erase(oldPos);
	  p->updateDateNextCommand(Server::Player::MOVE, c->date);
	  return (p->moveRight());
	}
    }
  return false;
}

bool
Server::Game::moveDown(Player *p, t_cmd *c)
{
  (void)c;
  if (p->getPosY() != this->_map->getHeight() - 1)
    {
      std::pair<size_t, size_t> pos(p->getPosX(), p->getPosY() + 1);
      std::pair<size_t, size_t> oldPos(p->getPosX(), p->getPosY());
      int			elem = this->_map->getElemAtPos(pos);

      if (elem == Map::B_BOMB || elem == Map::B_RANGE || elem == Map::B_SPEED)
	this->earnBonus(p, elem, pos);
      if (elem == Map::GROUND && this->_players.find(pos) == this->_players.end())
	{
	  this->_players[pos] = this->_players[oldPos];
	  this->_players.erase(oldPos);
	  p->updateDateNextCommand(Server::Player::MOVE, c->date);
	  return (p->moveDown());
	}
    }
  return false;
}

bool
Server::Game::moveLeft(Player *p, t_cmd *c)
{
  (void)c;
  if (p->getPosX())
    {
      std::pair<size_t, size_t> pos(p->getPosX() - 1, p->getPosY());
      std::pair<size_t, size_t> oldPos(p->getPosX(), p->getPosY());
      int			elem = this->_map->getElemAtPos(pos);

      if (elem == Map::B_BOMB || elem == Map::B_RANGE || elem == Map::B_SPEED)
	this->earnBonus(p, elem, pos);
      if (elem == Map::GROUND && this->_players.find(pos) == this->_players.end())
	{
	  this->_players[pos] = this->_players[oldPos];
	  this->_players.erase(oldPos);
	  p->updateDateNextCommand(Server::Player::MOVE, c->date);
	  return (p->moveLeft());
	}
    }
  return false;
}
