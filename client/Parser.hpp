//
// Parser.hpp for  in /home/franel_j/tek2/cpp/bomberman/client
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Sun Jun  8 15:49:48 2014 julie franel
// Last update Sun Jun  8 16:25:22 2014 julie franel
//

#ifndef		PARSER_HPP_
# define	PARSER_HPP_

# include	<string>
# include	<iostream>
# include	"AObject.hpp"
# include	"GameEntities.hpp"
# include	"EventsHandler.hpp"
# include	"SafeQueue.hpp"
# include	"macros.hpp"


class		Parser
{
  struct                        t_parser
  {
    size_t                      id;
    std::pair<size_t, size_t>   pos;
    std::string                 action;
    std::vector<std::string>    params;
  };

  GameEntities							&_gameEntities;
  SafeQueue<std::pair<std::pair<size_t, size_t>, int> >		&_createInstructs;

  std::map<std::string, AObject::EventIn>			_dir;
  std::map<std::string, ObjectType>				_types;
  std::map<std::string, void (Parser::*)(const t_parser &)>	_fct;



  t_parser              *parser(std::string cmd);
  void                  parseMove(const t_parser &_parser);
  void                  parseRotate(const t_parser &_parser);
  void                  parseCreate(const t_parser &_parser);
  void                  parseCreate(const std::list<t_parser *> &_tabParser);
  void                  parseDestroy(const t_parser &_parser);
  void                  displayParserStruct(const t_parser &parser);
  void                  handleActions(const t_parser &parser);
  void                  handleActions(std::list<t_parser *> &_parser);
public:
  Parser(GameEntities &gameEntities, SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs);
  ~Parser();

  void			run(std::string &string);
};

#endif		/* !PARSER_HPP */
