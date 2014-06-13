//
// MenuHandler.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Wed Jun 11 08:32:50 2014 aurelien prieur
// Last update Fri Jun 13 15:02:38 2014 virol_g
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

std::pair<int, bool>	MenuHandler::mainMenu()
{
  MainMenu	menu = MainMenu(*_sdlContext);
  t_game	*options;
  int		retVal;

  if (!(menu.initialize()) || !(menu.build()))
    return (std::pair<int, bool>(-1, false));
  while (menu.update())
    menu.draw();
  if ((options = menu.getChoice()) != NULL)
    {
      retVal = static_cast<int>(!options->isHost);
      delete options;
      return (std::pair<int, bool>(retVal, options->isDouble));
    }
  return (std::pair<int, bool>(-1, false));
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
	    Server::Server server(&connexionHandler);
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
  t_game	*choice = NULL;
  int		mode;
  bool		ret = true;
  std::pair<int, bool>	tmp;

  tmp = mainMenu();
  mode = tmp.first;
  if (mode == 0)
    menu = new CreateMenu(*_sdlContext);
  else if (mode == 1)
    menu = new JoinMenu(*_sdlContext);
  else
    return (NULL);
  if (!menu->initialize() || !menu->build())
    return (NULL);
  while (menu->update())
    menu->draw();
  _sdlContext->stop();
  delete _sdlContext;
  if ((choice = menu->getChoice()) != NULL)
    {
      choice->isDouble = tmp.second;
      std::cout << "Choice received" << std::endl;
      if (mode == 0)
	ret = createGame(choice);
      else if (mode == 1)
	ret = joinGame(choice);
    }
  if (!ret)
    return (NULL);
  return (choice);
}
