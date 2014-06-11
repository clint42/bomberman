//
// MenuHandler.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Wed Jun 11 08:32:50 2014 aurelien prieur
// Last update Wed Jun 11 15:13:22 2014 aurelien prieur
//

#include "MenuHandler.hpp"

MenuHandler::MenuHandler(Signal &signal): _signal(signal), _forked(false)
{
  _sdlContext = new gdl::SdlContext;
  _sdlContext->start(800, 600, "Menu", SDL_INIT_VIDEO, SDL_WINDOW_OPENGL);
}

MenuHandler::~MenuHandler()
{
}

pid_t	MenuHandler::forker() const
{
  return (fork());
}

int		MenuHandler::mainMenu()
{
  MainMenu	menu = MainMenu(*_sdlContext);
  t_game	*options;
  int		retVal;

  if (!(menu.initialize()) || !(menu.build()))
    return (-1);
  while (menu.update())
    {
      menu.draw();
      menu.timer();
    }
  if ((options = menu.getChoice()) != NULL)
    {
      retVal = static_cast<int>(!options->isHost);
      delete options;
      return (retVal);
    }
  return (-1);
}

bool	MenuHandler::createGame(t_game *options)
{
  pid_t	pid;
 
  if (!_forked)
    {
      pid = forker();
      if (pid == -1)
      	{
      	  std::cerr << "Failed to fork to create the server" << std::endl;
      	  return (false);
      	}
      if (pid == 0)
      	{
      	  ConnexionHandler	connexionHandler;

      	  Server::Server server(&connexionHandler);
      	  server.run();
	  exit(0);
      	}
      _signal.catchSignal(SIGCHLD, true);
      _forked = true;
    }
  options->ipAddr = "127.0.0.1";
  options->isHost = true;
  return (true);
}

bool	MenuHandler::joinGame(t_game *options)
{
  options->isHost = false;
  return (true);
}

t_game	*MenuHandler::launchMenus()
{
  AMenu		*menu;
  t_game	*choice = NULL;
  int		mode;

  mode = mainMenu();
  //TODO: in mode == 1, instanciate a SubMenu not a CreateMenu
  if (mode == 0)
    menu = new CreateMenu(*_sdlContext);
  else if (mode == 1)
    menu = new CreateMenu(*_sdlContext);
  else
    return (NULL);
  if (!menu->initialize() || !menu->build())
    return (NULL);
  while (menu->update())
    {
      menu->draw();
      menu->timer();
    }
  _sdlContext->stop();
  delete _sdlContext;
  choice = menu->getChoice();
  std::cout << "Choice received" << std::endl;
  if (mode == 0)
    createGame(choice);
  else if (mode == 1)
    joinGame(choice);
  return (choice);
}
