#include "Game.hpp"

static Server::Game::Play g_Plays[] = {
  { 0,  1,  1, 0, false, 0 },
  { 0,  1,  1, 0, false, RESPAWN_DELAY },
  { 4, 16,  1, 0, false, RESPAWN_DELAY },
  { 4, 16, 15, 2,  true, 0 }
};


Server::Game::Game(std::string const &m, size_t p, size_t b, size_t t, Type type,
		   std::list<Player *> const &peers, Messenger *mes, size_t &id)
  : _map(0), _params(g_Plays[type]), _time(static_cast<Time_t>(t)),
    _messenger(mes), _bombThread(0), _id(id),
    _started(false), _paused(false), _ended(false),
    _nbPlayers(p), _nbBots(b),
    _peers(peers)
{
  DEBUG("Server::Game::Game()", 1);

  if (!p || !t || (p + b < 2) || !mes)
    throw GameException("Invalid parameters");

  try {
    _map = new Map(m);
  }
  catch (MapException) {
    _map = 0;
    throw GameException("Map not found");
  }
  if (_nbPlayers > _map->getNbrSlot()) {
    _nbPlayers = _map->getNbrSlot();
  }
  if (_nbBots + _nbPlayers > _map->getNbrSlot())
    _nbBots = _map->getNbrSlot() - _nbPlayers;

  _messenger->broadcastMessage(std::string("0 0 0 MAP ") + m);
  DEBUG("! Server::Game::Game()", -1);
}

Server::Game::~Game() {
  t_cmd *c;

  delete _bombThread;
  delete _map;
  while (_events.tryPop(&c)) delete c;
  while (_bombs.tryPop(&c))  delete c;
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
  while (!_ended) {
    // std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
    if (_paused || !_bombs.tryPop(&c)) {
      // std::cout << "$$$$ j'entame le wait()" << std::endl;
      // _bombs.wait();
      // std::cout << "$$$$ je sors du wait()" << std::endl;
      usleep(75000);
    }
    else {
      // std::cout << "$$$$ j'ai reussi a pop un objet" << std::endl;
      if (!_bombs.empty()) {
	// _bombs.signal();
      }
      else {
	// std::cout << "$$$$ j'unlock pour pas avoir de delock" << std::endl;
      }
      // std::cout << "$$$$ je fais l'execution" << std::endl;
      { // code
	if (this->timeLeft() > c->date) {
	  // std::cout << "[SERVER] Server::Game::bombsProcessing() => time of usleep " << this->timeLeft().inUsec() - c->date.inUsec() << "." << std::endl;
	  usleep(this->timeLeft().inUsec() - c->date.inUsec());
	}
	else {
	  // DEBUG("[SERVER] Server::Game::bombsProcessing() => en fait, elle explose directe", 0);
	}
	if (_paused) {
	  _bombs.push_front(c);
	} else {
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
    _endAt = _startedAt + Time(0, GAME_TIME * _time, COUNTDOWN);
    this->updateTimeLeft();
    for (std::map<std::pair<size_t, size_t>, Player *>::iterator it = _players.begin();
	 it != _players.end(); ++it) {
      (it->second)->updateDateNextCommand(Server::Player::ORIENT, this->timeLeft() - Time(0, 0, COUNTDOWN));
    }
    _bombThread = new Thread(&Server::Game::trampoline_bombsProcessing, this);
    _started = true;
    std::stringstream ss;
    ss << "0 0 0 STARTGAME " << this->timeLeft().inSec() << "\n";
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
      this->createBots();
      this->start();
    }
  }
  else if (this->isEnded()) {
    _ended = true;
    _messenger->broadcastMessage("0 0 0 ENDGAME");
  }
  else {
    // Creer fonction qui itere sur tous les bots / pour chacun des bots faire une action
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


void			Server::Game::saveGame() const
{
  time_t		seed = time(0);
  struct tm		*t = localtime(&seed);
  std::ofstream		file;
  std::string		name;
  std::stringstream	ss;
  size_t x = 0;
  size_t y = 0;

  ss << "save/" << (t->tm_year + 1900) << "-" << (t->tm_mon + 1) << "-" << t->tm_mday
     << "-" << t->tm_hour << "h" << t->tm_min << "m" << t->tm_sec << "s.save";
  name = ss.str();

  file.open(name.c_str(), std::ios::out | std::ios::trunc);
  if (file.is_open())
    {
      file << this->getMap()->getWidth() << std::endl;
      file << this->getMap()->getHeight() << std::endl;
      file << this->getMap()->getNbrSlot() << std::endl;
      while (y < this->getMap()->getHeight())
	{
	  x = 0;
	  while (x < this->getMap()->getWidth())
	    {
	      std::pair<size_t, size_t> pos(x, y);
	      file << this->getMap()->getElemAtPos(pos);
	      ++x;
	    }
	  file << std::endl;
	  ++y;
	}
      file << "SETTINGS" << std::endl;
      file << this->timeLeft() << std::endl;
      for (std::map<std::pair<size_t, size_t>, Player *>::const_iterator it = this->_players.begin();
	   it != this->_players.end(); ++it)
	{
	  file << it->second->getPosX() << " " << it->second->getPosY() << " " <<
	    it->second->getScore() << std::endl;
	}
      file.close();
    }
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
  std::cout << "X = " << _posx << " | Y = " << _posy << std::endl;
  std::cout << "X = " << _map->getWidth() << " | Y = " << _map->getHeight() << std::endl;
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
      this->_players[pos] = (*it);
      DEBUG("Server::Game::pickPlayers() => un peer est devenu un player", -1);
      msg << "0 0 0 CREATE PLAYER " << (*it)->getID() << " " << (*it)->getPosX() << " " << (*it)->getPosY() << "\n";
      _messenger->broadcastMessage(msg.str());
      std::cout << "<< " << msg.str() << std::endl;
      msg.str(std::string());
      msg.clear();
    }
  } // !for
  DEBUG("! Server::Game::pickPlayers()", -1);
}

void
Server::Game::createBots() {
  Player *			p;
  std::pair<size_t, size_t>     pos;
  std::stringstream msg;

  for (size_t n = 0; n < _nbBots; ++n) {
    p = new Player(_id, 0, true);
    _bots.push_back(new Bot(p, _map, _players));
    pos = this->generatePos(-1, -1);
    p->setPos(pos.first, pos.second);
    this->_players[pos] = p;
    msg << "0 0 0 CREATE PLAYER " << p->getID() << " "
	<< p->getPosX() << " " << p->getPosY() << "\n";
    _messenger->broadcastMessage(msg.str());
    msg.str(std::string());
    msg.clear();
    ++_id;
  }
  // Player *			p;
  // std::pair<size_t, size_t>     pos;
  // std::stringstream msg;

  // for (size_t n = 0; n < _nbBots; ++n) {
  //   p = new Player(_id, 0, true);
  //   _bots.push_back(new Bot(p, _map));
  //   pos = this->generatePos(-1, -1);
  //   p->setPos(pos.first, pos.second);
  //   this->_players[pos] = p;
  //   msg << "0 0 0 CREATE PLAYER " << p->getID() << " "
  // 	<< p->getPosX() << " " << p->getPosY() << "\n";
  //   _messenger->broadcastMessage(msg.str());
  //   msg.str(std::string());
  //   msg.clear();
  //   ++_id;
  // }
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
  this->_map->deleteElem(pos);
  convert << "0 " << pos.first << " " << pos.second << " DESTROY\n";
  this->_messenger->broadcastMessage(convert.str());
}

void
Server::Game::bombSwitchQueue(t_cmd *c, const std::pair<size_t, size_t> pos)
{
  t_cmd * cmd = new t_cmd;
  cmd->id = c->id;
  std::cout << "[SERVER] Server::Game::bomSwitchQueue() => before calcul" << c->date << std::endl;
  cmd->date = c->date - Time(0, 0, BOMBTIME);
  std::cout << "[SERVER] Server::Game::bomSwitchQueue() => after calcul" << cmd->date << std::endl;
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
  c->params.push_back("BOMB");
  c->params.push_back("0");
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
