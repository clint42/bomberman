//
// MenuHandler.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Wed Jun 11 08:21:25 2014 aurelien prieur
// Last update Wed Jun 11 14:50:41 2014 aurelien prieur
//

#ifndef MENUHANDLER_HPP_
# define MENUHANDLER_HPP_

#include <unistd.h>
#include <SdlContext.hh>
#include "AMenu.hpp"
#include "MainMenu.hpp"
#include "CreateMenu.hpp"
#include "Signal.hpp"
#include "ConnexionHandler.hpp"
#include "../server/Server.hpp"

class	MenuHandler
{
private:
  gdl::SdlContext	*_sdlContext;
  Signal		&_signal;
  int			mainMenu();
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
