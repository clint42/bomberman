#include	"Game.hpp"
#include	"Types.hpp"

std::map<int, std::string> getDirection;

Server::Game::Bot::Bot(Server::Player *p, Map *m, std::map<std::pair<size_t, size_t>, Server::Player *> &list):
  _p(p), _map(m), _list(list)
{
  getDirection[0] = "UP";
  getDirection[1] = "RIGHT";
  getDirection[2] = "DOWN";
  getDirection[3] = "LEFT";
}

Server::Game::Bot::~Bot() {
}

void
Server::Game::Bot::attack() {

}

void
Server::Game::Bot::actionBot(const Time &date, SafeQueue<t_cmd *> &events)
{
  int		warning;

  warning = this->danger();
  if (warning == 0)
    this->attack();
  else
    {
      int	i = 0;

      while (warning > 0)
	{
	  if (warning % 10 == 1)
	    {
	      Server::t_cmd	*cmd = new t_cmd;
	      cmd->id = this->_p->getID();
	      cmd->date = date;
	      cmd->pos = std::pair<size_t, size_t>(this->_p->getPosX(), this->_p->getPosY());
	      cmd->action = "MOVE";
	      cmd->params.push_back(getDirection[i]);
	      events.push(cmd);
	      return ;
	    }
	  warning /= 10;
	  ++i;
	}
    }
  (void)_list;
}

bool
Server::Game::Bot::danger()
{
  int	ret = 0;
  int	val = -1;
  std::pair<size_t, size_t>	pos(this->_p->getPosX(), this->_p->getPosY());

  while (this->_p->getPosY() + val > 0 && (size_t)(val * -1) < 3)
    {
      pos.second = this->_p->getPosY() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB || (val == -1 && (this->_map->getElemAtPos(pos) == Map::WALL ||
								       this->_map->getElemAtPos(pos) == Map::DWALL ||
								       this->_list.find(pos) != this->_list.end())))
	{
	  ret = 1;
	  break;
	}
      --val;
    }
  val = 1;
  pos.second = this->_p->getPosY();
  while (this->_p->getPosX() + val < this->_map->getWidth() - 1 && (size_t)val < 3)
    {
      pos.first = this->_p->getPosX() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB || (val == 1 && (this->_map->getElemAtPos(pos) == Map::WALL || this->_map->getElemAtPos(pos) == Map::DWALL || this->_list.find(pos) != this->_list.end())))
	{
	  ret += 10;
	  break;
	}
      ++val;
    }
  val = 1;
  pos.first = this->_p->getPosX();
  while (this->_p->getPosY() + val < this->_map->getHeight() && (size_t)val < 3)
    {
      pos.second = this->_p->getPosY() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB || (val == 1 && (this->_map->getElemAtPos(pos) == Map::WALL || this->_map->getElemAtPos(pos) == Map::DWALL || this->_list.find(pos) != this->_list.end())))
	{
	  ret += 100;
	  break;
	}
      ++val;
    }
  val = -1;
  pos.second = this->_p->getPosY();
  while (this->_p->getPosX() + val > 0 && (size_t)(val * -1) < 3)
    {
      pos.first = this->_p->getPosX() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB || (val == -1 && (this->_map->getElemAtPos(pos) == Map::WALL || this->_map->getElemAtPos(pos) == Map::DWALL || this->_list.find(pos) != this->_list.end())))
	{
	  ret += 1000;
	  break;
	}
      --val;
    }
  return (ret);
}
