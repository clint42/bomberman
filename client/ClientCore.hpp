//
// ClientCore.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
//
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
//
// Started on  Thu May 29 15:42:09 2014 aurelien prieur
// Last update Wed Jun 11 19:00:56 2014 aurelien prieur
//

#ifndef CLIENTCORE_HPP_
# define CLIENTCORE_HPP_

# include <utility>
# include "Socket.hpp"
# include "GameEntities.hpp"
# include "EventsHandler.hpp"
# include "SafeQueue.hpp"
# include "macros.hpp"
# include "AMenu.hpp"
# include "MapRender.hpp"

class		Parser;

class		ClientCore
{
  class		Configurator
  {
    std::vector<std::string>	_cmds;
    bool			_error;
    t_game			*_options;
  public:
    Configurator(t_game *options);
    ~Configurator();
    void	pushCmd(std::string const &cmd);
    void	popCmd(std::string &cmd);
    int		sizeCmd(void) const;
    void	errorOccured(void);
    bool	hasErrorOccured(void) const;
    t_game const	*getOptions(void) const;
  };
  Configurator		*_configurator;
  int			_playerId;
  GameEntities		&_gameEntities;
  EventsHandler		&_eventsHandler;
  Socket		*_socket;
  ConnexionHandler	&_connexion;
  SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &_createInstructs;
  Parser		*_parser;
  MapRender		*_map;
  bool			read(void);
  bool			write(void);
  bool			connectServer(t_game *options);
  bool			loadMap(t_game *options);
  void			buildConfigCmd(std::string &string) const;
  void			buildMapMd5(std::string &string, int playerId) const;
  bool			isConfigured(void) const;
  static void		trampoline(void *param, Socket *socket, bool b[3]);
  static void		trampolineConfig(void *param, Socket *socket, bool b[3]);

public:
  ClientCore(GameEntities &gameEntities, EventsHandler &eventsHandler,
	     SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs,
	     ConnexionHandler &connexionHandler);
  ~ClientCore();
  bool		initialize(t_game *options);
  void		config(Socket *socket, bool b[3]);
  bool		run();
  void		io(Socket *socket, bool b[3]);
};

#endif // !CLIENTCORE_HPP_
