#include	"Game.hpp"

Server::Game::Bot::Bot(Server::Player *p, Map *m, std::map<std::pair<size_t, size_t>, Server::Player *> &list):
  _p(p), _map(m), _list(list)
{
  // (void)_p;
  // (void)_map;
  // (void)_list;
}

Server::Game::Bot::~Bot()
{
}

void
Server::Game::Bot::actionBot()
{
  (void)_list;
}

bool
Server::Game::Bot::danger()
{
  int	ret = 0;
  int	val = 1;
  std::pair<size_t, size_t>	pos(this->_p->getPosX(), this->_p->getPosY());

  while (this->_p->getPosX() + val < this->_map->getWidth() - 1 && (size_t)val < 3)
    {
      pos.first = this->_p->getPosX() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB || (val == 1 && (this->_map->getElemAtPos(pos) == Map::WALL || this->_map->getElemAtPos(pos) == Map::DWALL)))
	{
	  ret = 1;
	  break;
	}
      ++val;
    }
  val = -1;
  pos.first = this->_p->getPosX();
  while (this->_p->getPosX() + val > 0 && (size_t)(val * -1) < 3)
    {
      pos.first = this->_p->getPosX() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB || (val == -1 && (this->_map->getElemAtPos(pos) == Map::WALL || this->_map->getElemAtPos(pos) == Map::DWALL)))
	{
	  ret += 10;
	  break;
	}
      --val;
    }
  val = -1;
  pos.first = this->_p->getPosX();
  while (this->_p->getPosY() + val > 0 && (size_t)(val * -1) < 3)
    {
      pos.second = this->_p->getPosY() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB || (val == -1 && (this->_map->getElemAtPos(pos) == Map::WALL || this->_map->getElemAtPos(pos) == Map::DWALL)))
	{
	  ret += 100;
	  break;
	}
      --val;
    }
  val = 1;
  pos.second = this->_p->getPosY();
  while (this->_p->getPosY() + val < this->_map->getHeight() && (size_t)val < 3)
    {
      pos.second = this->_p->getPosY() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB || (val == 1 && (this->_map->getElemAtPos(pos) == Map::WALL || this->_map->getElemAtPos(pos) == Map::DWALL)))
	{
	  ret += 1000;
	  break;
	}
      ++val;
    }
  return (ret);
}
