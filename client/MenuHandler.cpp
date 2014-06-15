//
// MenuHandler.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Wed Jun 11 08:32:50 2014 aurelien prieur
// Last update Sun Jun 15 20:51:09 2014 virol_g
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

t_game		*MenuHandler::mainMenu()
{
  MainMenu	menu = MainMenu(*_sdlContext);
  t_game	*options;
  int		retVal;

  if (!(menu.initialize()) || !(menu.build()))
    return (NULL);
  while (menu.update())
    menu.draw();
  if ((options = menu.getChoice()) != NULL)
    {
      retVal = static_cast<int>(!options->isHost);
    }
  return (options);
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
	  
	  try {
	    Server::Server server(&connexionHandler, options->serverPort);
	    server.run();
	  }
	  catch (ConnexionException e) {
	    std::cerr << "Couldn't launch server: " << e.what() << std::endl;
	  }
	  _exit(0);
      	}
      if (!_signal.catchSignal(SIGCHLD, true))
	return (false);
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
  t_game	*mainChoice;
  t_game	*choice = NULL;
  int		mode;
  bool		ret = true;

  if ((mainChoice = mainMenu()) == NULL)
    return (NULL);
  mode = static_cast<int>(mainChoice->selected);
  if (mode == 0)
    menu = new CreateMenu(*_sdlContext);
  else if (mode == 1)
    menu = new JoinMenu(*_sdlContext);
  else if (mode == 2)
    menu = new LoadMenu(*_sdlContext);
  else
    return (NULL);
  if (!menu->initialize() || !menu->build())
    return (NULL);
  while (menu->update())
    menu->draw();
  if ((choice = menu->getChoice()) != NULL)
    {
      if (choice->createMap == true)
	{
	  MapMenu	*mapMenu = new MapMenu(*_sdlContext);

	  if (!mapMenu->initialize() || !mapMenu->build())
	    {
	      _sdlContext->stop();
	      delete _sdlContext;
	      return (NULL);
	    }
	  while (mapMenu->update())
	    mapMenu->draw();
	  choice->heightMap = mapMenu->getInfo("Map height");
	  choice->widthMap = mapMenu->getInfo("Map width");
	  choice->playersMap = mapMenu->getInfo("Players on the map");
	  choice->mapName = mapMenu->getMapName();
	}

      choice->isDouble = mainChoice->isDouble;
      delete mainChoice;
      if (mode == 0)
	ret = createGame(choice);
      else if (mode == 1)
	ret = joinGame(choice);
    }
  _sdlContext->stop();
  delete _sdlContext;
  if (!ret)
    {

      return (NULL);
    }
  return (choice);
}
