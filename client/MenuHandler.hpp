//
// MenuHandler.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Wed Jun 11 08:21:25 2014 aurelien prieur
// Last update Sun Jun 15 12:33:35 2014 virol_g
//

#ifndef MENUHANDLER_HPP_
# define MENUHANDLER_HPP_

# include <unistd.h>
# include <SdlContext.hh>
# include "AMenu.hpp"
# include "MainMenu.hpp"
# include "MapMenu.hpp"
# include "CreateMenu.hpp"
# include "JoinMenu.hpp"
# include "LoadMenu.hpp"
# include "Signal.hpp"
# include "ConnexionHandler.hpp"
# include "../server/Server.hpp"

class	MenuHandler
{
private:
  gdl::SdlContext	*_sdlContext;
  Signal		&_signal;
  t_game		*mainMenu();
  bool			createGame(t_game *options);
  bool			joinGame(t_game *options);
  pid_t			forker() const;
  bool			_forked;

public:
  MenuHandler(Signal &signal);
  ~MenuHandler();
  t_game	*launchMenus();
};

#endif // !MENUHANDLER_HPP_
