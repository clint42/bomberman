//
// ClientCore.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
//
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
//
// Started on  Thu May 29 15:44:40 2014 aurelien prieur
// Last update Sun Jun 15 23:25:39 2014 buret_j
//

#include "Parser.hpp"


/*
** CTOR /DTOR
*/

Parser::Parser(GameEntities &gameEntities,
	       SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs,
	       EventsHandler &eventsHandler):
  _gameEntities(gameEntities),
  _createInstructs(createInstructs),
  _eventsHandler(eventsHandler)
{
  this->_dir["UP"] = AObject::UP;
  this->_dir["RIGHT"] = AObject::RIGHT;
  this->_dir["DOWN"] = AObject::DOWN;
  this->_dir["LEFT"] = AObject::LEFT;

  this->_types["BLOCK"] = BLOCK;
  this->_types["BOMB"] = BOMB;
  this->_types["FIRE"] = FIRE;
  this->_types["PLAYER"] = PLAYER;
  this->_types["B_BOMB"] = BONUSBOMB;
  this->_types["B_SPEED"] = BONUSSPEED;
  this->_types["B_RANGE"] = BONUSRANGE;

  this->_fct["MOVE"] = &Parser::parseMove;
  this->_fct["CREATE"] = &Parser::parseCreate;
  this->_fct["ROTATE"] = &Parser::parseRotate;
  this->_fct["DESTROY"] = &Parser::parseDestroy;
  this->_fct["CHRONO"] = &Parser::parseChrono;
  this->_fct["SCORE"] = &Parser::parsePoint;
  this->_fct["STARTGAME"] = &Parser::parseStartGame;
  this->_fct["ENDGAME"] = &Parser::parseEndGame;
  this->_fct["PAUSE"] = &Parser::parseStartGame; // StartGame is handling pause
  this->_fct["VICTORY"] = &Parser::parseVictory;

  this->_fct["WELCOME"] = &Parser::parseWelcome;
  this->_fct["MAP"] = &Parser::parseMap;

  this->_tabFct["CREATE"] = &Parser::parseCreate;
  this->_tabFct["DESTROY"] = &Parser::parseDestroy;

  this->_config.idPlayer1 = 0;
  this->_config.idPlayer2 = 0;
  this->_config.mapName = "";
  this->_config.welcomeReceived = false;
}

Parser::~Parser()
{

}



/*
** GETTER
*/

const Parser::t_config	&Parser::getConfig() const
{
  return (this->_config);
}

/*
** MEMBER FUNCTIONS - GAME ENTITIES
*/

void		Parser::parseMove(const t_parser &_parser)
{
  static int	nbMove = 0;

  this->_gameEntities.moveEntity(_parser.pos, this->_dir[_parser.params.front()]);
  ++nbMove;
}

void		Parser::parseChrono(const t_parser &_parser)
{
  size_t	_chrono;

  CVRT_STRING_TO_SIZET(_parser.params[0], _chrono);
  this->_gameEntities.setTimeLeft(static_cast<float>(_chrono));
}

void		Parser::parseCreate(const t_parser &_parser)
{
  size_t	posx;
  size_t	posy;
  size_t	id;

  CVRT_STRING_TO_SIZET(_parser.params[1], id);
  CVRT_STRING_TO_SIZET(_parser.params[2], posx);
  CVRT_STRING_TO_SIZET(_parser.params[3], posy);
  this->_createInstructs.push(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(posx, posy),
								  this->_types[_parser.params[0]] + id));
}

bool		Parser::parseCreate(std::list<t_parser *> &_tabParser)
{
  std::list<std::pair<std::pair<size_t, size_t>, int> >		_list;
  bool ret = false;

  for (std::list<t_parser *>::iterator it = _tabParser.begin(); it != _tabParser.end(); ++it)
    {
      if ((*it)->action.compare("CREATE") == 0)
	{
	  size_t posx;
	  size_t posy;
	  size_t id;

	  CVRT_STRING_TO_SIZET((*it)->params[1], id);
	  CVRT_STRING_TO_SIZET((*it)->params[2], posx);
	  CVRT_STRING_TO_SIZET((*it)->params[3], posy);
	  _list.push_back(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(posx, posy),
								    this->_types[(*it)->params[0]] + id));
	  _tabParser.erase(it);
	  it = _tabParser.begin();
	  ret = true;
	}
    }
  this->_createInstructs.push(_list);
  return (ret);
}

void		Parser::parseDestroy(const t_parser &_parser)
{
  this->_gameEntities.deleteEntity(_parser.pos);
}

bool		Parser::parseDestroy(std::list<t_parser *> &_tabParser)
{
  std::list<t_parser *>::iterator it;
  bool	ret = false;

  for (it = _tabParser.begin(); it != _tabParser.end(); ++it)
    {
      if ((*it)->action.compare("DESTROY") == 0)
	{
	  this->_gameEntities.deleteEntity((*it)->pos);
	  _tabParser.erase(it);
	  it = _tabParser.begin();
	  ret = true;
	}
    }
  return (ret);
}

void		Parser::parseRotate(const t_parser &_parser)
{
  this->_gameEntities.rotateEntity(_parser.pos, this->_dir[_parser.params.front()]);
}


void		Parser::parseWelcome(const t_parser &_parser)
{
  if (this->_config.idPlayer1 == 0)
    this->_config.idPlayer1 = _parser.id;
  else if (this->_config.idPlayer2 == 0)
    this->_config.idPlayer2 = _parser.id;
  this->_config.welcomeReceived = true;
}

void		Parser::parseMap(const t_parser &_parser)
{
  this->_config.mapName = _parser.params.front();
}

void		Parser::parseStartGame(const t_parser &_parser)
{
  size_t        _chrono;

  CVRT_STRING_TO_SIZET(_parser.params[0], _chrono);
  this->_gameEntities.setTimeLeft(static_cast<float>(_chrono));
  this->_gameEntities.startGame();
}


void		Parser::parsePoint(const t_parser &_parser)
{
  size_t	points;

  CVRT_STRING_TO_SIZET(_parser.params.front(), points);
  this->_gameEntities.addPoints(points, _parser.id);
}


void		Parser::parseEndGame(__attribute__((unused))const t_parser &_parser)
{
  this->_eventsHandler.endGame();
}

void		Parser::parseVictory(__attribute__((unused))const t_parser &_parser)
{
  size_t	idWinner;

  CVRT_STRING_TO_SIZET(_parser.params.front(), idWinner);
  this->_eventsHandler.setWinner(idWinner);
}


/*
** MEMBER FUNCTIONS - PROCESS FUNCTIONS
*/

void		Parser::displayParserStruct(const t_parser &_parser)
{
  for (std::vector<std::string>::const_iterator it = _parser.params.begin(); it != _parser.params.end(); ++it)
    {
      std::cout << "\t[" << *it << "]" << std::endl;
    }
}

Parser::t_parser	*Parser::parser(std::string cmd)
{
  size_t	pos1 = 0;
  size_t	pos2 = 0;
  size_t	posx;
  size_t	posy;
  t_parser	*_parser = new t_parser;

  pos1 = cmd.find(" "); // recup id
  CVRT_STRING_TO_SIZET(cmd.substr(0, pos1), _parser->id);
  pos2 = cmd.find(" ", pos1 + 1); // recup posx
  CVRT_STRING_TO_SIZET(cmd.substr(pos1 + 1, pos2 - (pos1 + 1)), posx);
  pos1 = cmd.find(" ", pos2 + 1); // recup posy
  CVRT_STRING_TO_SIZET(cmd.substr(pos2 + 1, pos1 - (pos2 + 1)), posy);
  _parser->pos = std::pair<size_t, size_t>(posx, posy);
  pos2 = cmd.find(" ", pos1 + 1); // recup action
  _parser->action = cmd.substr(pos1 + 1, pos2 - (pos1 + 1));
  if ((pos1 = cmd.find(" ", pos2 + 1)) != std::string::npos)
    while ((pos1 = cmd.find(" ", pos2 + 1)) != std::string::npos) // recup chaque param
      {
	_parser->params.push_back(cmd.substr(pos2 + 1, pos1 - (pos2 + 1)));
	pos2 = pos1;
      }
  _parser->params.push_back(cmd.substr(pos2 + 1, pos1 - (pos2 + 1)));
  return (_parser);
}

void		Parser::handleActions(const t_parser &_parser)
{
  std::map<std::string, void (Parser::*)(const t_parser &)>::iterator	it;

  for (it = this->_fct.begin(); it != this->_fct.end(); ++it)
    {
      if (it->first == _parser.action)
	(this->*it->second)(_parser);
    }
}

void		Parser::handleActions(std::list<t_parser *> &_tabParser)
{
  std::list<t_parser *>::iterator itTab;
  bool ret = false;

  for (itTab = _tabParser.begin(); itTab != _tabParser.end(); ++itTab)
    {
      if (ret == true)
	{
	  itTab = _tabParser.begin();
	  ret = false;
	}
      ret = (this->*_tabFct[(*itTab)->action])(_tabParser);
    }
}

void		Parser::runSplit(std::string string)
{
  size_t	pos1 = 0;
  size_t	pos2 = -1;
  t_parser	*_parser;

  if ((pos1 = string.find(";", pos2 + 1)) != std::string::npos)
    {
      std::list<t_parser *>	_tabParser;

      while ((pos1 = string.find(";", pos2 + 1)) != std::string::npos)
	{
	  _parser = this->parser(string.substr(pos2 + 1, pos1 - (pos2 + 1)));
	  _tabParser.push_back(_parser);
	  pos2 = pos1;
	  if ((pos1 = string.find(";", pos2 + 1)) == std::string::npos)
	    {
	      _parser = this->parser(string.substr(pos2 + 1, pos1 - (pos2 + 1)));
	      _tabParser.push_back(_parser);
	    }
	}
      this->handleActions(_tabParser);
    }
  else
    {
      _parser = this->parser(string);
      this->handleActions(*_parser);
    }
}

void		Parser::run(std::string &string)
{
  size_t	pos1 = 0;
  size_t	pos2 = -1;

  if (string.find("\n") != std::string::npos)
    {
      while ((pos1 = string.find("\n", pos2 + 1)) != std::string::npos)
	{
	  this->runSplit(string.substr(pos2 + 1, pos1 - (pos2 + 1)));
	  pos2 = pos1;
	  if ((pos1 = string.find("\n", pos2 + 1)) == std::string::npos)
	    this->runSplit(string.substr(pos2 + 1, pos1 - (pos2 + 1)));
	}
    }
  else
    this->runSplit(string);
}
