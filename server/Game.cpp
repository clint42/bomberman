#include "Game.hpp"

static Server::Game::Play g_Plays[] = {
  { 0,  1,  1, 0, false, 0 },
  { 0,  1,  1, 0, false, RESPAWN_DELAY },
  { 4, 16,  1, 0, false, RESPAWN_DELAY },
  { 4, 16, 15, 2,  true, 0 }
};


Server::Game::Game(std::string const &m, size_t p, size_t b, size_t t, Type type,
		   std::list<Player *> const &peers, Messenger *mes)
  : _map(0), _params(g_Plays[type]), _time(static_cast<Time_t>(t)), _messenger(mes), _bombThread(0),
    _started(false), _paused(false),
    _nbPlayers(p), _nbBots(b), _round(0),
    _peers(peers)
{
  (void)_round;
  DEBUG("Server::Game::Game()", 1);

  if (!p || !t || !mes)
    throw GameException("Invalid parameters");

  try {
    _map = new Map(std::string("./maps/") + m);
  }
  catch (MapException) {
    _map = 0;
    throw GameException("Map not found");
  }
  if (_nbPlayers > _map->getNbrSlot()) {
    _nbPlayers = _map->getNbrSlot();
    p = _nbPlayers;
  }
  if (_nbBots + _nbPlayers > _map->getNbrSlot())
    _nbBots = _map->getNbrSlot() - _nbPlayers;

  _messenger->broadcastMessage(std::string("0 0 0 MAP ") + m);
  DEBUG("! Server::Game::Game()", -1);
}

Server::Game::~Game() {
  delete _map;
  delete _bombThread;
}

void *
Server::Game::trampoline_bombsProcessing(void *g) {
  static_cast<Server::Game *>(g)->bombsProcessing();
  return NULL;
}

void
Server::Game::bombsProcessing() {
  t_cmd *	c;

  DEBUG("Server::Game::bombsProcessing", 1);
  while (!this->isEnded()) {
    DEBUG("Server::Game:: TEST0", 0);
    if (_paused || !_bombs.tryPop(&c)) {
      DEBUG("Server::Game:: TEST1", 0);
      _bombs.wait();
    } else {
      DEBUG("Server::Game:: TEST2", 0);
      if (!_bombs.empty()) {
	DEBUG("Server::Game:: TEST3", 0);
	_bombs.signal();
      }
      { // code
	DEBUG("Server::Game:: TEST4", 0);
	if (this->timeLeft() > c->date) {
	  std::cout << "[SERVER] Server::Game::bombsProcessing() => time of usleep " << this->timeLeft().usec() - c->date.usec() << "." << std::endl;
	  usleep(this->timeLeft().usec() - c->date.usec());
	}
	else {
	  DEBUG("[SERVER] Server::Game::bombsProcessing() => en fait, elle explose directe", 0);
	}
	if (_paused) {
	  _bombs.push_front(c);
	} else {
	  DEBUG("Server::Game:: TEST5", 0);
	  if (c->action == "BOMB")
	    c->action += " EXPLOSE";
	  _events.push_front(c);
	}
      } // !code
      // delete c; // pas delete puisqu'on repush !! sigsegf autrement...
    }
  }
  DEBUG("!Server::Game::bombsProcessing", -1);
}

void
Server::Game::start() {
  DEBUG("Server::Game::start()", 1);
  if (!_started) {
    DEBUG("Server::Game::start() => le jeu n'etait pas demarre", 0);
    _startedAt.now();
    _endAt = _startedAt + Time(0, GAME_TIME * _time);
    this->updateTimeLeft();

    DEBUG("Server::Game::start() => le jeu n'etait pas demarre => check point 1", 0);
    _bombThread = new Thread(&Server::Game::trampoline_bombsProcessing, this); // create bombs' thread
    DEBUG("Server::Game::start() => le jeu n'etait pas demarre => check point 2", 0);
    _started = true;
    std::stringstream ss;
    ss << "0 0 0 STARTGAME " << this->timeLeft().sec() << "\n";
    std::cout << "<< " << ss.str() << std::endl;
    _messenger->broadcastMessage(ss.str());
    DEBUG("Server::Game::start() => le jeu n'etait pas demarre => check point 2", 0);
  }
  else if (_paused) {
    DEBUG("Server::Game::start() => on redemarre apres une pause", 0);
    Time t;
    t.now();
    _endAt += t - _pausedAt;
    _paused = false;
    _bombs.signal(); // unpause bomb thread (var cond)
  }
  DEBUG("! Server::Game::start()", -1);
}

void
Server::Game::pause() {
  if (_started && !_paused) {
    _pausedAt.now();
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

size_t
Server::Game::countPeersThatCertified() const {
  size_t n = 0;
  for (std::list<Player *>::const_iterator it = _peers.begin();
       it != _peers.end(); ++it) {
    if ((*it)->hasCertified())
      ++n;
  }
  return n;
}

void
Server::Game::update() {
  DEBUG("Server::Game::update()", 1);
  Player *p = NULL;

  if (!_started) {
    if (this->countPeersThatCertified() < _nbPlayers) {
      DEBUG("! Server::Game::update() => on a voulu lancer, mais pas assez de joueurs OK", -1);
      return ;
    }
    else {
      this->pickPlayers(_nbPlayers);
      this->start();
    }
  }
  else if (this->isEnded()) {
  }
  else {
    t_cmd *c;
    if (!_events.tryPop(&c)) {
      DEBUG("! Server::Game::update()", -1);
      return ;
    }
    if (_players.find(c->pos) != _players.end())
      p = _players[c->pos];
    if ((!p || p->getID() != c->id) && c->action == "BOMB EXPLOSE")
      {
      p = this->findPlayerByID(c->id);
      	DEBUG("Server::Game::update() => Find player by ID", 0);
      }
    if (!p || p->getID() != c->id)
      {
	DEBUG("Server::Game::update() => player not found", 0);
	if (!p)
	  {
	    DEBUG("Server::Game::update() => P faux", 0);
	  }
        else if (p->getID() != c->id)
	  {
	    DEBUG("Server::Game::update() => ID incorrect", 0);
	  }
	delete c;
	DEBUG("! Server::Game::update()", -1);
	return ;
      }

    if (this->process(c, p)) {
      DEBUG("Server::Game::update() => process returned true", 0);
      this->filterCmd(c);
      _messenger->broadcastMessage(c->msg);
    }
    else
      DEBUG("! Server::Game::update() => process return false", 0);
    delete c;
    DEBUG("! Server::Game::update()", -1);
  }
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
  std::cout << "MSG = " << cmd->msg << std::endl;
}

/*
** PROCESS
*/

std::pair<size_t, size_t>
Server::Game::generatePos(const size_t posx, const size_t posy) {
  size_t                        _posx;
  size_t                        _posy;

  _posx = rand() % this->_map->getWidth();
  _posy = rand() % this->_map->getHeight();
  std::pair<size_t, size_t> pos(_posx, _posy);
  if ((_posx == posx && _posy == posy) ||
      (this->_map->getElemAtPos(_posx, _posy) != 0) ||
      (this->_players.find(pos) != this->_players.end()))
    return (this->generatePos(_posx, _posy));
  return (pos);
}

void
Server::Game::pickPlayers(size_t nb) {
  DEBUG("Server::Game::pickPlayers()", 1);
  std::stringstream msg;
  for (std::list<Player *>::const_iterator it = this->_peers.begin();
       it != this->_peers.end() && nb; ++it, --nb) {

    if ((*it)->hasCertified()) {
      std::pair<size_t, size_t>     pos = this->generatePos(-1, -1);
      (*it)->setPos(pos.first, pos.second);
      (*it)->updateDateNextCommand(Server::Player::ORIENT, this->timeLeft());
      this->_players[pos] = (*it);
      DEBUG("Server::Game::pickPlayers() => un peer est devenu un player", -1);
      msg << "0 0 0 CREATE PLAYER " << (*it)->getID() << " " << (*it)->getPosX() << " " << (*it)->getPosY() << "\n";
      _messenger->broadcastMessage(msg.str());
      std::cout << "<< " << msg.str() << std::endl;
      msg.clear();
    }
  } // !for
  DEBUG("! Server::Game::pickPlayers()", -1);
}

void
Server::Game::earnBonus(Player *p, int bonus, const std::pair<size_t, size_t> pos)
{
  std::stringstream convert;
  if (bonus == Map::B_BOMB)
    p->earnBomb();
  else if (bonus == Map::B_RANGE)
    p->earnRange();
  else
    p->earnSpeed();
  convert << "0 " << pos.first << " " << pos.second << " DESTROY";
  this->_messenger->broadcastMessage(convert.str());
}

void
Server::Game::bombSwitchQueue(t_cmd *c, const std::pair<size_t, size_t> pos)
{
  t_cmd * cmd = new t_cmd;
  cmd->id = c->id;
  cmd->date = c->date;
  cmd->pos = pos;
  cmd->action = c->action;
  std::cout << "Avant push dans _bombs" << std::endl;
  this->_bombs.push(cmd);
  std::cout << "Apres push dans _bombs" << std::endl;
}

void
Server::Game::buildCmdCreateBomb(t_cmd *c, const std::pair<size_t, size_t> pos)
{
  c->action = "CREATE";
  c->params.resize(2);
  c->params[0] = "BOMB";
  c->params[1] = "0";
  std::stringstream convert;
  convert << pos.first;
  c->params.push_back(convert.str());
  convert.str(std::string());
  convert.clear();
  convert << pos.second;
  c->params.push_back(convert.str());
  std::cout << "[" <<c->params[2] << "]" << std::endl;
  std::cout << "[" <<c->params[3] << "]" << std::endl;
}

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
  DEBUG("Server::Game::bombUp()", -1);
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
  DEBUG("Server::Game::bombRight()", -1);
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
  DEBUG("Server::Game::bombDown()", -1);
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
  DEBUG("Server::Game::bombLeft()", -1);
	  return (p->dropBomb());
	}
    }
  return false;
}

void
Server::Game::createBonus(const std::pair<size_t, size_t> pos, t_cmd *c, int ret)
{
  int		val = rand() % 7;

  if (ret == Map::DWALL && (val == Map::B_BOMB || val == Map::B_RANGE || val == Map::B_SPEED))
    {
      std::stringstream convert;
      this->_map->setElemAtPos(pos, val);
      convert << ";0 0 0 CREATE " << _bonus[val] << " 0 " << pos.first << " " << pos.second;
      c->msg += convert.str();
    }
  else
    this->_map->deleteElem(pos);
}

bool Server::Game::_isGame = false;
std::map<std::pair<Server::Player::Action, Server::Player::Dir>,
	 bool (Server::Game::*)(Server::Player *, Server::t_cmd *)> Server::Game::func;
std::map<int, std::string> Server::Game::_bonus;

bool
Server::Game::process(t_cmd *c, Player *p)
{
  DEBUG("Server::Game::process()", 1);
  if (!this->hasDateNextCommandExpired(p))
    {
      DEBUG("!Server::Game::process() ==> pas le droit de faire une action", -1);
      return false;
    }

  Server::Player::Action a;
  Server::Player::Dir	 d;
  if (_isGame == false)
    {
      _isGame = true;
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
      _bonus[Map::B_BOMB] = "B_BOMB";
      _bonus[Map::B_RANGE] = "B_RANGE";
      _bonus[Map::B_SPEED] = "B_SPEED";
    }
  if (c->action == "MOVE")
    {
      std::cout << "PROCESS Players size = " << _players.size() << std::endl;
      p->getAction(&a, &d, c->params[0]);
      DEBUG("!Server::Game::process() ==> verifier les actions de process => if", -1);
      return ((this->*func[std::pair<Server::Player::Action, Server::Player::Dir>(a, d)])(p, c));
    }
  else if (c->action == "BOMB")
    {
      a = Server::Player::BOMB;
      d = p->getOrientation();
      DEBUG("!Server::Game::process() ==> verifier les actions de process => else if", -1);
      return ((this->*func[std::pair<Server::Player::Action, Server::Player::Dir>(a, d)])(p, c));
    }
  else if (c->action == "BOMB EXPLOSE")
    {
      this->bombExplose(p, c);
      this->_messenger->broadcastMessage(c->msg);
      std::cout << "Return false mais c'est normal" << std::endl;
      // send directly to messenger
    }
  DEBUG("! Server::Game::process()", -1);
  return (false);
}

void
Server::Game::killPlayer(const std::pair<size_t, size_t> pos)
{
  if (_players[pos]->isBot())
    delete _players[pos];
  this->_players.erase(pos);
}

void
Server::Game::killPlayer(Player *p) {
  (void)p;
}



/*
** EXCEPTION
*/

GameException::GameException(const std::string &msg) throw(): ABombermanException(msg) {}
GameException::~GameException(void) throw() {}
