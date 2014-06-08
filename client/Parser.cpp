//
// ClientCore.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
//
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
//
// Started on  Thu May 29 15:44:40 2014 aurelien prieur
// Last update Sun Jun  8 16:26:44 2014 julie franel
//

#include "Parser.hpp"


/*
** CTOR /DTOR
*/

Parser::Parser(GameEntities &gameEntities,
	       SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs):
  _gameEntities(gameEntities),
  _createInstructs(createInstructs)

{
  this->_dir["UP"] = AObject::UP;
  this->_dir["RIGHT"] = AObject::RIGHT;
  this->_dir["DOWN"] = AObject::DOWN;
  this->_dir["LEFT"] = AObject::LEFT;

  this->_types["BLOCK"] = BLOCK;
  this->_types["BOMB"] = BOMB;
  this->_types["FIRE"] = FIRE;
  this->_types["PLAYER"] = PLAYER;

  this->_fct["MOVE"] = &Parser::parseMove;
  this->_fct["CREATE"] = &Parser::parseCreate;
  this->_fct["ROTATE"] = &Parser::parseRotate;
  this->_fct["DESTROY"] = &Parser::parseDestroy;
}

Parser::~Parser()
{

}


/*
** MEMBER FUNCTIONS - GAME ENTITIES
*/

void		Parser::parseMove(const t_parser &_parser)
{
  this->_gameEntities.moveEntity(_parser.pos, this->_dir[_parser.params.front()]);
}

void		Parser::parseCreate(const t_parser &_parser)
{
  size_t posx;
  size_t posy;

  CVRT_STRING_TO_SIZET(_parser.params[1], posx);
  CVRT_STRING_TO_SIZET(_parser.params[2], posy);
  this->_createInstructs.push(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(posx, posy),
								  this->_types[_parser.params.front()]));
}

void		Parser::parseCreate(const std::list<t_parser *> &_tabParser)
{
  std::list<std::pair<std::pair<size_t, size_t>, int> >		_list;

  for (std::list<t_parser *>::const_iterator it = _tabParser.begin(); it != _tabParser.end(); ++it)
    {
      size_t posx;
      size_t posy;

      CVRT_STRING_TO_SIZET((*it)->params[1], posx);
      CVRT_STRING_TO_SIZET((*it)->params[2], posy);
      _list.push_back(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(posx, posy),
								this->_types[(*it)->params[0]]));
    }
  this->_createInstructs.push(_list);
}

void		Parser::parseDestroy(const t_parser &_parser)
{
  this->_gameEntities.deleteEntity(_parser.pos);
}

void		Parser::parseRotate(const t_parser &_parser)
{
  this->_gameEntities.rotateEntity(_parser.pos, this->_dir[_parser.params.front()]);
}



/*
** MEMBER FUNCTIONS - PROCESS FUNCTIONS
*/

void		Parser::displayParserStruct(const t_parser &_parser)
{
  std::cout << "ID = [" << _parser.id << "]" << std::endl;
  std::cout << "POSX = [" << _parser.pos.first << "]" << std::endl;
  std::cout << "POSY = [" << _parser.pos.second << "]" << std::endl;
  std::cout << "ACTION = [" << _parser.action << "]" << std::endl;
  std::cout << "PARAMS = " << std::endl;
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

void		Parser::handleActions(std::list<t_parser *> &_parser)
{
  if (_parser.front()->action == "DESTROY")
    {
      this->parseDestroy(*_parser.front());
      _parser.pop_front();
      if (_parser.front()->action == "CREATE")
	this->parseCreate(_parser);
    }
}

void		Parser::run(std::string &string)
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
