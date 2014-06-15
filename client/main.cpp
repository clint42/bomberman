//
// main.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
//
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
//
// Started on  Fri May 16 15:53:47 2014 aurelien prieur
// Last update Sun Jun 15 22:59:16 2014 aurelien prieur
//

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "GameEntities.hpp"
#include "EventsHandler.hpp"
#include "ThreadUI.hpp"
#include "ClientCore.hpp"
#include "SafeQueue.hpp"
#include "AObject.hpp"
#include "Signal.hpp"
#include "MenuHandler.hpp"

//TODO: testing purpose only. Remove it.
extern int debug_align;
int debug_align = 0;

int	main()
{
  srand(time(0));

  ConnexionHandler	connexionHandler;
  Signal		signal(&connexionHandler);
  signal.catchSignal(SIGINT, false);

  MenuHandler menuHandler(signal);
  menuHandler.initialize();
  t_game	*options;

  if ((options = (menuHandler.launchMenus())) == NULL)
    return (EXIT_FAILURE);

  EventsHandler		eventsHandler(connexionHandler);
  GameEntities		gameEntities;
  SafeQueue<std::pair<std::pair<size_t, size_t>, int> >	createInstructs;

  ClientCore	core(gameEntities, eventsHandler, createInstructs, connexionHandler);

  if (!core.initialize(options))
    {
      std::cerr << "Initialization failure" << std::endl;
      return (EXIT_FAILURE);
    }

  ThreadUI	threadUI(eventsHandler, gameEntities, createInstructs);
  core.run();
  std::cout << "After core.run()" << std::endl;
  threadUI.join();
  return (EXIT_SUCCESS);
}
