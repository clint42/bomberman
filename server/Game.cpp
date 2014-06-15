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
    _botsThread(0),
    _started(false), _paused(false), _ended(false),
    _nbPlayers(p), _nbBots(b),
    _peers(peers)
{

  if (m.find(".save") != std::string::npos)
    this->_toLoad = true;
  else
    this->_toLoad = false;

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
}

Server::Game::~Game() {
  t_cmd *c;

  delete _bombThread;
  delete _botsThread;
  delete _map;
  while (_events.tryPop(&c)) delete c;
  while (_bombs.tryPop(&c))  delete c;
  for (std::list<Bot *>::iterator it = _bots.begin(); it != _bots.end(); ++it) {
    std::pair<size_t, size_t> pos((*it)->getPlayer()->getPosX(), (*it)->getPlayer()->getPosY());
    this->killPlayer(pos);
  }
  if (_players.size()) {
    
    _messenger->broadcastMessage("");
  }
}

void *
Server::Game::trampoline_bombsProcessing(void *g) {
  static_cast<Server::Game *>(g)->bombsProcessing();
  return NULL;
}

void
Server::Game::bombsProcessing() {
  t_cmd *	c;

  while (!_ended) {
    if (_paused || !_bombs.tryPop(&c)) {
      usleep(75000);
    }
    else {
      if (this->timeLeft() > c->date) {
	usleep(this->timeLeft().inUsec() - c->date.inUsec());
      }
      if (_paused) {
	_bombs.push_front(c);
      } else {
	if (c->action == "BOMB")
	  c->action += " EXPLOSE";
	_events.push_front(c);
      }
    }
  }
}

void
Server::Game::start() {
  if (!_started) {
    _startedAt.now();
    _endAt = _startedAt + Time(0, GAME_TIME * _time, COUNTDOWN);
    this->updateTimeLeft();
    for (std::map<std::pair<size_t, size_t>, Player *>::iterator it = _players.begin();
	 it != _players.end(); ++it) {
      (it->second)->updateDateNextCommand(Server::Player::ORIENT, this->timeLeft() - Time(0, 0, COUNTDOWN + 1));
    }
    _bombThread = new Thread(&Server::Game::trampoline_bombsProcessing, this);
    _botsThread = new Thread(&Server::Game::trampoline_botsProcessing, this);
    _started = true;
    std::stringstream ss;
    ss << "0 0 0 STARTGAME " << this->timeLeft().inSec() << "\n";
    _messenger->broadcastMessage(ss.str());
  }
  else if (_paused) {
    std::stringstream ss;
    _endAt += Time().now() - _pausedAt;
    _paused = false;
    ss << "0 0 0 PAUSE " << this->timeLeft().inSec() << "\n";
    _messenger->broadcastMessage(ss.str());
  }
}

void
Server::Game::pause() {
  if (_started && !_paused) {
    std::stringstream ss;
    ss << "0 0 0 PAUSE " << this->timeLeft().inSec() << "\n";
    _pausedAt.now();
    _paused = true;
    _messenger->broadcastMessage(ss.str());
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
  Player *p = NULL;

  if (!_started) {
    if (this->countPeersThatCertified() < _nbPlayers) {
      return ;
    }
    else {
      this->pickPlayers(_nbPlayers);
      this->createBots();
      if (this->_toLoad == true)
	this->loadGame(this->_map->getFilename());
      this->start();
    }
  }
  else if (this->isEnded()) {
    _ended = true;
    _messenger->broadcastMessage("0 0 0 ENDGAME");
  }
  else {
    t_cmd *c;
    if (!_events.tryPop(&c)) {
      return ;
    }
    if (_players.find(c->pos) != _players.end())
      p = _players[c->pos];
    if ((!p || p->getID() != c->id) && c->action == "BOMB EXPLOSE")
      {
	p = this->findPlayerByID(c->id);
      }
    if (!p || p->getID() != c->id)
      {
	delete c;
	return ;
      }

    if (this->process(c, p)) {
      this->filterCmd(c);
      _messenger->broadcastMessage(c->msg);
    }
    delete c;
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

  ss << "save/" << this->getNbrPlayers() << "-" << this->getNbrBots() << "-"
     << (t->tm_year + 1900) << "-" << (t->tm_mon + 1) << "-" << t->tm_mday << "-"
     << t->tm_hour << "h" << t->tm_min << "m" << t->tm_sec << "s.save";
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
      file << this->timeLeft().inSec() << std::endl;
      for (std::map<std::pair<size_t, size_t>, Player *>::const_iterator it = this->_players.begin();
	   it != this->_players.end(); ++it)
	{
	  file << it->second->isBot() << " " << it->second->getPosX() << " " << it->second->getPosY()
	       << " " << it->second->getScore() << std::endl;
	}
      file.close();
    }
}


void		Server::Game::loadGame(const std::string &filename)
{
  std::ifstream file(filename.c_str(), std::ios::in);
  std::string   readed;
  std::vector<std::string>	_infos;

  if (file.is_open())
    {
      while (std::getline(file, readed) && readed.compare("SETTINGS") != 0);
      while (std::getline(file, readed))
	_infos.push_back(readed);
      file.close();

      size_t	nbrBots = 0;
      size_t	nbrPlayers = 0;
      size_t	pos1 = filename.find("/");
      size_t	pos2 = filename.find("-", pos1);
      size_t	timeLeft;
      size_t	count = 1;
      size_t	posX = 0;
      size_t	posY = 0;
      bool	isBot = false;
      size_t	score = 0;

      CVRT_STRING_TO_SIZET(filename.substr(pos1 + 1, pos2 - pos1 - 1), nbrPlayers);

      pos1 = filename.find("-", pos2);
      CVRT_STRING_TO_SIZET(filename.substr(pos2 + 1, pos1 - pos2 - 1), nbrBots);

      CVRT_STRING_TO_SIZET(_infos[0], timeLeft);
      this->setTimeLeft(timeLeft);

      this->pickPlayers(nbrBots + nbrPlayers);
      for (std::map<std::pair<size_t, size_t>, Player *>::iterator it = this->_players.begin();
	   it != this->_players.end(); ++it)
      	{
	  if (count <= (nbrBots + nbrPlayers) && count <= _infos.size())
	    {
	      pos1 = 0;
	      pos2 = 0;
	      pos1 = _infos[count].find(" ");
	      isBot = _infos[count].substr(0, pos1).compare("1") == 0 ? true : false;

	      pos2 = _infos[count].find(" ", pos1 + 1);
	      CVRT_STRING_TO_SIZET(_infos[count].substr(pos1 + 1, pos2 - pos1 - 1), posX);

	      pos1 = _infos[count].find(" ", pos2 + 1);
	      CVRT_STRING_TO_SIZET(_infos[count].substr(pos2 + 1, pos1 - pos2 - 1), posY);

	      pos2 = _infos[count].find(" ", pos1 + 1);
	      CVRT_STRING_TO_SIZET(_infos[count].substr(pos1 + 1, pos2 - pos1 - 1), score);

	      (*it).second->setPos(posX, posY);
	      (*it).second->setBot(isBot);
	      (*it).second->setScore(score);
	      ++count;
	    }
      	}
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
  std::pair<size_t, size_t> pos(_posx, _posy);
  if ((_posx == posx && _posy == posy) ||
      (this->_map->getElemAtPos(_posx, _posy) != 0) ||
      (this->_players.find(pos) != this->_players.end()))
    return (this->generatePos(_posx, _posy));
  return (pos);
}

void
Server::Game::pickPlayers(size_t nb) {
  std::stringstream msg;
  for (std::list<Player *>::const_iterator it = this->_peers.begin();
       it != this->_peers.end() && nb; ++it, --nb) {

    if ((*it)->hasCertified()) {
      std::pair<size_t, size_t>     pos = this->generatePos(-1, -1);
      (*it)->setPos(pos.first, pos.second);
      this->_players[pos] = (*it);
      msg << "0 0 0 CREATE PLAYER " << (*it)->getID() << " " << (*it)->getPosX() << " " << (*it)->getPosY() << "\n";
      _messenger->broadcastMessage(msg.str());
      msg.str(std::string());
      msg.clear();
    }
  } // !for
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
  cmd->date = c->date - Time(0, 0, BOMBTIME);
  cmd->pos = pos;
  cmd->action = c->action;
  this->_bombs.push(cmd);
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
  if (!this->hasDateNextCommandExpired(p))
    {
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
    }
  return (false);
}

void
Server::Game::killPlayer(const std::pair<size_t, size_t> pos)
{
  if (_players[pos]->isBot())
    {
      for (std::list<Bot *>::iterator it = _bots.begin(); it != _bots.end(); ++it)
	{
	  if (*it && ((*it)->getPlayer()->getPosX() == pos.first && (*it)->getPlayer()->getPosY() == pos.second))
	    {
	      this->_bots.erase(it);
	      break;
	    }
	}
      delete _players[pos];
    }
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
