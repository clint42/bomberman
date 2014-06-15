#include	"Game.hpp"
#include	"Types.hpp"

std::map<int, std::string> getDirection;

Server::Game::Bot::Bot(Server::Player *p, Map *m, std::map<std::pair<size_t, size_t>, Server::Player *> &list):
  _p(p), _map(m), _list(list), _way(4)
{
  getDirection[0] = "UP";
  getDirection[1] = "RIGHT";
  getDirection[2] = "DOWN";
  getDirection[3] = "LEFT";
}

Server::Game::Bot::~Bot()
{
}

void
Server::Game::Bot::attack()
{

}

bool
Server::Game::Bot::isFull(bool b)
{
  for (size_t i = 0; i < 4; ++i)
    if (_way[i] != b)
      return (false);
  return (true);
}

void
Server::Game::Bot::actionBot(const Time &date, SafeQueue<t_cmd *> &events)
{
  int		r;

  for (size_t i = 0; i < 4; ++i)
    _way[i] = true;
  this->danger();
  if (this->isFull(true) || this->isFull(false))
    this->attack();
  else
    while (1)
      {
	r = rand() % 4;
	if (_way[r] == true)
	  {
	    Server::t_cmd	*cmd = new t_cmd;
	    cmd->id = this->_p->getID();
	    cmd->date = date;
	    cmd->pos = std::pair<size_t, size_t>(this->_p->getPosX(), this->_p->getPosY());
	    cmd->action = "MOVE";
	    cmd->params.push_back(getDirection[r]);
	    events.push(cmd);
	    return ;
	  }
      }
  (void)_list;
}

void
Server::Game::Bot::danger()
{
  int	val = -1;
  std::pair<size_t, size_t>	pos(this->_p->getPosX(), this->_p->getPosY());

  while ((size_t)(val * -1) < 3)
    {
      pos.second = this->_p->getPosY() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB || (val == -1 && (this->_map->getElemAtPos(pos) == Map::WALL || this->_map->getElemAtPos(pos) == Map::DWALL || this->_list.find(pos) != this->_list.end())))
	{
	  _way[0] = false;
	  break;
	}
      --val;
    }
  val = 1;
  pos.second = this->_p->getPosY();
  while ((size_t)val < 3)
    {
      pos.first = this->_p->getPosX() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB || (val == 1 && (this->_map->getElemAtPos(pos) == Map::WALL || this->_map->getElemAtPos(pos) == Map::DWALL || this->_list.find(pos) != this->_list.end())))
	{
	  _way[1] = false;
	  break;
	}
      ++val;
    }
  val = 1;
  pos.first = this->_p->getPosX();
  while ((size_t)val < 3)
    {
      pos.second = this->_p->getPosY() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB || (val == 1 && (this->_map->getElemAtPos(pos) == Map::WALL || this->_map->getElemAtPos(pos) == Map::DWALL || this->_list.find(pos) != this->_list.end())))
	{
	  _way[2] = false;
	  break;
	}
      ++val;
    }
  val = -1;
  pos.second = this->_p->getPosY();
  while ((size_t)(val * -1) < 3)
    {
      pos.first = this->_p->getPosX() + val;
      if (this->_map->getElemAtPos(pos) == Map::BOMB || (val == -1 && (this->_map->getElemAtPos(pos) == Map::WALL || this->_map->getElemAtPos(pos) == Map::DWALL || this->_list.find(pos) != this->_list.end())))
	{
	  _way[3] = false;
	  break;
	}
      --val;
    }
}
