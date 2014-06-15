//
// Parser.hpp for  in /home/franel_j/tek2/cpp/bomberman/client
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Sun Jun  8 15:49:48 2014 julie franel
// Last update Sun Jun 15 22:40:31 2014 virol_g
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

  struct			t_config
  {
    size_t			idPlayer1;
    size_t			idPlayer2;
    std::string			mapName;
    bool			welcomeReceived;
  };

  GameEntities							&_gameEntities;
  SafeQueue<std::pair<std::pair<size_t, size_t>, int> >		&_createInstructs;
  EventsHandler							&_eventsHandler;
  t_config							_config;

  std::map<std::string, AObject::EventIn>			_dir;
  std::map<std::string, ObjectType>				_types;
  std::map<std::string, void (Parser::*)(const t_parser &)>	_fct;
  std::map<std::string, bool (Parser::*)(std::list<t_parser *> &)>	_tabFct;

  t_parser              *parser(std::string cmd);

  void                  parseWelcome(const t_parser &_parser);
  void                  parseMap(const t_parser &_parser);
  void                  parseStartGame(const t_parser &_parser);
  void			parseEndGame(const t_parser &_parser);
  void            Parser::parseVictory(__attribute__((unused))const t_parser &_parser);

  void                  parseMove(const t_parser &_parser);
  void                  parseRotate(const t_parser &_parser);
  void                  parseCreate(const t_parser &_parser);
  void                  parseDestroy(const t_parser &_parser);
  void			parseChrono(const t_parser &_parser);
  void			parsePoint(const t_parser &_parser);

  bool                  parseCreate(std::list<t_parser *> &_tabParser);
  bool                  parseDestroy(std::list<t_parser *> &_tabParser);

  void                  displayParserStruct(const t_parser &parser);
  void                  handleActions(const t_parser &parser);
  void                  handleActions(std::list<t_parser *> &_parser);

  void			runSplit(std::string string);

public:
  Parser(GameEntities &gameEntities,
	 SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs,
	 EventsHandler &eventsHandler);
  ~Parser();

  void			run(std::string &string);

  const t_config	&getConfig() const;
};

#endif		/* !PARSER_HPP */
