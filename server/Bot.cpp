#include	"Game.hpp"

Server::Bot::Bot(Player *p, Map *m, const std::map<std::pair<size_t, size_t>, Player *> &list):
  _p(p), _map(m), _list(list)
{
  (void)_p;
  (void)_map;
  (void)_list;
}

Server::Bot::~Bot()
{
}

Server::Bot::actionBot()
{
  
}

Server::Bot::danger()
{
  int	ret = 0;
  int	val = 1;
  std::pair<size_t, size_t>	pos(this->_p->getPosX(), this->_p->getPosY());
  
  while (this->_p->getPosX() + val < this->_map->getWidth() - 1 && (size_t)val < 3)
    {
      pos.first = this->_p->getPosX() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB)
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
      if (this->_map->getElemAtPos(pos) == Map::BOMB)
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
      if (this->_map->getElemAtPos(pos) == Map::BOMB)
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
      if (this->_map->getElemAtPos(pos) == Map::BOMB)
	{
	  ret += 1000;
	  break;
	}
      ++val;
    }
  return (ret);
}
