#include "Game.hpp"

static Server::Game::Play g_Plays[] = {
  { 0,  1,  1, 0, false, 0 },
  { 0,  1,  1, 0, false, RESPAWN_DELAY },
  { 4, 16,  1, 0, false, RESPAWN_DELAY },
  { 4, 16, 15, 2,  true, 0 }
};


Server::Game::Game(std::string const &m, size_t p, size_t b, size_t t, Type type,
		   std::list<Player *> const &peers, Messenger *mes)
  : _map(0), _params(g_Plays[type]), _time(static_cast<Time>(t)), _messenger(mes),
    _started(false), _paused(false),
    _maxPlayers(p), _maxBots(b), _round(0),
    _peers(peers) {
  (void)_round;
  DEBUG("Server::Game::Game()", 1);

  try {
    _map = new Map(m);
  } catch (MapException) {
      _map = 0;
      throw GameException("Map not found");
    }
    if (_maxPlayers > _map->getNbrSlot()) {
      _maxPlayers = _map->getNbrSlot();
      p = _maxPlayers;
    }
    if (_maxBots + _maxPlayers > _map->getNbrSlot())
      _maxBots = _map->getNbrSlot() - _maxPlayers;

    _messenger->broadcastMessage(std::string("0 0 0 MAP ") + m);

    // for (std::list<Player *>::const_iterator it = peers.begin(); p && it != peers.end(); ++it, --p) {
    //   _players[(*it)->getPos()] = *it;
    // } // we have to retrieve players at end of countdown, not here
  DEBUG("! Server::Game::Game()", -1);
}

Server::Game::~Game() {
  delete _map;
}

void *
Server::Game::trampoline_bombsProcessing(void *g) {
  static_cast<Server::Game *>(g)->bombsProcessing();
  return NULL;
}

void
Server::Game::bombsProcessing() {
  t_cmd *	c;

  while (!this->isEnded()) {
    if (_paused || !_bombs.tryPop(&c)) {
      _bombs.wait();
    } else {
      if (!_bombs.empty())
	_bombs.signal();
      { // code
	if (this->timeLeft() - c->date > 0)
	  usleep(this->timeLeft() - c->date);
	if (_paused) {
	  _bombs.push_front(c);
	} else {
	  if (c->action == "BOMB") c->action += " EXPLOSE";
	  _events.push_front(c);
	}
      } // !code
      // delete c; // pas delete puisqu'on repush !! sigsegf autrement...
    }
  }

}

void
Server::Game::start() {
  if (!_started) {
    gettimeofday(&_startedAt, NULL);
    _endAt.tv_usec = _startedAt.tv_usec + (GAME_TIME * _time * 60 * 1000000);
    _endAt.tv_sec = _endAt.tv_usec / 1000000;
    Thread(&Server::Game::trampoline_bombsProcessing, this); // create bombs' thread
    _started = true;
    (void)_peers;
  } else if (_paused) {
    timeval tmp;
    gettimeofday(&tmp, NULL);
    _endAt.tv_usec += tmp.tv_usec - _pausedAt.tv_usec;
    _paused = false;
    _bombs.signal(); // unpause bomb thread (var cond)
  }
}

size_t
Server::Game::timeLeft() const {
  if (!_paused) {
    timeval tmp;
    gettimeofday(&tmp, NULL);
    return _endAt.tv_sec - tmp.tv_sec;
  }
  return _endAt.tv_sec - _pausedAt.tv_sec;
}

void
Server::Game::pause() {
  if (_started && !_paused) {
    gettimeofday(&_pausedAt, NULL);
    _paused = true;
  }
}

Server::Player *
Server::Game::findPlayerByID(const size_t id)
{
  (void)id;
  for (std::map<std::pair<size_t, size_t>, Player *>::iterator it = this->_players.begin();
       it != this->_players.end(); ++it)
    {
      if (!!(*it).second)
	if ((*it).second->getID() == id)
	  return (*it).second;
    }
  return 0;
}

void
Server::Game::update() {
  DEBUG("Server::Game::update()", 1);

  t_cmd *c;
  if (!_events.tryPop(&c))
    return ;

  Player *p = _players[c->pos];
  if ((!p || p->getID() != c->id) && c->action == "BOMB EXPLOSE")
    p = this->findPlayerByID(c->id);
  if (!p || p->getID() != c->id) {
    DEBUG("! Server::Game::update() => player not found", 0);
    delete c;
    return ;
  }

  if (this->process(c, p)) {
    this->filterCmd(c);
    _messenger->broadcastMessage(c->msg);
  }
  delete c;
  DEBUG("! Server::Game::update()", 0);
}

void
Server::Game::filterCmd(t_cmd *cmd) const {
  std::stringstream convert;

  convert << cmd->id << " " << cmd->pos.first << " " <<
    cmd->pos.second << " " << cmd->action;
  cmd->msg = convert.str();
  for (std::vector<std::string>::const_iterator it = cmd->params.begin();
       it != cmd->params.end(); ++it) {
    convert.str(std::string());
    convert.clear();
    convert << " " << *it;
    cmd->msg += convert.str();
  }
  cmd->msg += "\n";
}

/*
** PROCESS
*/

bool
Server::Game::moveUp(Player *p, t_cmd *c)
{
  (void)c;
  if (p->getPosY())
    {
      std::pair<size_t, size_t> pos(p->getPosX(), p->getPosY() - 1);
      std::pair<size_t, size_t> oldPos(p->getPosX(), p->getPosY());
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end())
	{
	  this->_players[pos] = this->_players[oldPos];
	  this->_players.erase(oldPos);
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
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end())
	{
	  this->_players[pos] = this->_players[oldPos];
	  this->_players.erase(oldPos);
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
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end())
	{
	  this->_players[pos] = this->_players[oldPos];
	  this->_players.erase(oldPos);
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
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end())
	{
	  this->_players[pos] = this->_players[oldPos];
	  this->_players.erase(oldPos);
	  return (p->moveLeft());
	}
    }
  return false;
}

bool
Server::Game::orientUp(Player *p, t_cmd *c)
{
  c->action = "ROTATE";
  return(p->orient(Server::Player::UP));
}

bool
Server::Game::orientRight(Player *p, t_cmd *c)
{
  c->action = "ROTATE";
  return(p->orient(Server::Player::RIGHT));
}

bool
Server::Game::orientDown(Player *p, t_cmd *c)
{
  c->action = "ROTATE";
  return(p->orient(Server::Player::DOWN));
}

bool
Server::Game::orientLeft(Player *p, t_cmd *c)
{
  c->action = "ROTATE";
  return(p->orient(Server::Player::LEFT));
}

void
Server::Game::bombSwitchQueue(t_cmd *c, const std::pair<size_t, size_t> pos)
{
  t_cmd * cmd = new t_cmd;
  cmd->id = c->id;
  cmd->date = c->date;
  cmd->pos = pos;
  cmd->action = c->action;
  this->_bombs.push(cmd);
}

void
Server::Game::buildCmdCreateBomb(t_cmd *c, const std::pair<size_t, size_t> pos)
{
  c->action = "CREATE";
  c->params[0] = "BOMB";
  c->params[1] = "0";
  std::stringstream convert;
  convert << pos.first;
  c->params.push_back(convert.str());
  convert.str(std::string());
  convert.clear();
  convert << pos.second;
  c->params.push_back(convert.str());
}

bool
Server::Game::bombUp(Player *p, t_cmd *c)
{
  if (p->getPosY())
    {
      std::pair<size_t, size_t> pos(p->getPosX(), p->getPosY() - 1);
      if (!this->_map->getElemAtPos(pos) && this->_players.find(pos) == this->_players.end() &&
	  p->getBombsLimit() > p->getBombsOnFloor())
	{
	  this->bombSwitchQueue(c, pos);
	  this->buildCmdCreateBomb(c, pos);
	  this->_map->setElemAtPos(pos, Map::BOMB);
	  return (p->dropBomb());
	}
    }
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
	  this->bombSwitchQueue(c, pos);
	  this->buildCmdCreateBomb(c, pos);
	  this->_map->setElemAtPos(pos, Map::BOMB);
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
	  this->bombSwitchQueue(c, pos);
	  this->buildCmdCreateBomb(c, pos);
	  this->_map->setElemAtPos(pos, Map::BOMB);
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
	  this->bombSwitchQueue(c, pos);
	  this->buildCmdCreateBomb(c, pos);
	  this->_map->setElemAtPos(pos, Map::BOMB);
	  return (p->dropBomb());
	}
    }
  return false;
}

bool
Server::Game::exploseCase(const std::pair<size_t, size_t> pos, t_cmd *c)
{
  std::stringstream convert;
  int		ret;
  std::map<std::pair<size_t, size_t>, Player *>::iterator it;

  if ((ret = this->_map->getElemAtPos(pos)))
    {
      if (ret == Map::DWALL)
	{
	  convert << ";0 " << pos.first << " " << pos.second << " DESTROY";
	  convert << ";0 " << pos.first << " " << pos.second << " FIRE";
	  this->_map->setElemAtPos(pos, Map::GROUND);
	  c->msg += convert.str();
	}
      if (ret == Map::WALL || ret == Map::DWALL || ret == Map::BOMB)
	return (false);
    }
  else if ((it = this->_players.find(pos)) != this->_players.end())
    {
      convert << ";" << (*it).second->getID() << " " << pos.first << " " << pos.second << " DESTROY";
      convert << ";0 " << pos.first << " " << pos.second << " FIRE";
      c->msg += convert.str();
    }
  return (true);
}

void
Server::Game::bombExplose(Player *p, t_cmd *c)
{
  int		val = 1;
  std::stringstream convert;
  std::pair<size_t, size_t> pos(p->getPosX(), p->getPosY());

  this->_map->setElemAtPos(pos, Map::GROUND);
  convert << "0 " << pos.first << " " << pos.second << " DESTROY";
  convert << ";0 " << pos.first << " " << pos.second << " FIRE";
  c->msg = convert.str();
  // RIGHT
  while (p->getPosX() + val < this->_map->getWidth() - 1 && (size_t)val <= p->getBombRange())
    {
      pos.first = p->getPosX() + val;
      if (this->exploseCase(pos, c) == false)
	break ;
      ++val;
    }
  // LEFT
  val = -1;
  while (p->getPosX() + val > 0 && (size_t)(val * -1) <= p->getBombRange())
    {
      pos.first = p->getPosX() + val;
      if (this->exploseCase(pos, c) == false)
	break ;
      --val;
    }
  // UP
  val = -1;
  while (p->getPosY() + val > 0 && (size_t)(val * -1) <= p->getBombRange())
    {
      pos.first = p->getPosX();
      pos.first = p->getPosY() + val;
      if (this->exploseCase(pos, c) == false)
	break ;
      --val;
    }
  // DOWN
  val = 1;
  while (p->getPosY() + val < this->_map->getWidth() - 1 && (size_t)val <= p->getBombRange())
    {
      pos.second = p->getPosY() + val;
      if (this->exploseCase(pos, c) == false)
	break ;
      ++val;
    }
  c->msg += "\n";
}

bool Server::Game::_isGame = false;
std::map<std::pair<Server::Player::Action, Server::Player::Dir>,
	 bool (Server::Game::*)(Server::Player *, Server::t_cmd *)> Server::Game::func;

bool
Server::Game::process(t_cmd *c, Player *p)
{
  if (!this->hasDateNextCommandExpired(p))
    return false;

  Server::Player::Action a;
  Server::Player::Dir	 d;

  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::MOVE, Server::Player::UP)] = &Server::Game::moveUp;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::MOVE, Server::Player::RIGHT)] = &Server::Game::moveRight;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::MOVE, Server::Player::DOWN)] = &Server::Game::moveDown;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::MOVE, Server::Player::LEFT)] = &Server::Game::moveLeft;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::ORIENT, Server::Player::UP)] = &Server::Game::orientUp;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::ORIENT, Server::Player::RIGHT)] = &Server::Game::orientRight;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::ORIENT, Server::Player::DOWN)] = &Server::Game::orientDown;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::ORIENT, Server::Player::LEFT)] = &Server::Game::orientLeft;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::BOMB, Server::Player::UP)] = &Server::Game::bombUp;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::BOMB, Server::Player::RIGHT)] = &Server::Game::bombRight;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::BOMB, Server::Player::DOWN)] = &Server::Game::bombDown;
  func[std::pair<Server::Player::Action, Server::Player::Dir>(Server::Player::BOMB, Server::Player::LEFT)] = &Server::Game::bombLeft;
  if (c->action == "MOVE")
    {
      p->getAction(&a, &d, c->params[0]);
      return ((this->*func[std::pair<Server::Player::Action, Server::Player::Dir>(a, d)])(p, c));
    }
  else if (c->action == "BOMB")
    {
      a = Server::Player::BOMB;
      d = p->getOrientation();
      return ((this->*func[std::pair<Server::Player::Action, Server::Player::Dir>(a, d)])(p, c));
    }
  else if (c->action == "BOMB EXPLOSE")
    {
      this->bombExplose(p, c);
      this->_messenger->broadcastMessage(c->msg);
      // send directly to messenger
    }
  return (false);
}

void
Server::Game::killPlayer(Player *p) {
  (void)p;
}
