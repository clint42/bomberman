//
// main.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 15:53:47 2014 aurelien prieur
// Last update Wed Jun 11 15:09:14 2014 aurelien prieur
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

  Signal		signal;
  //TODO: Move to the right place. Testing purpose only.
  MenuHandler menuHandler(signal);
  t_game	*options;

  options = (menuHandler.launchMenus());
  ConnexionHandler	connexionHandler;
  EventsHandler		eventsHandler(connexionHandler);
  GameEntities		gameEntities;
  SafeQueue<std::pair<std::pair<size_t, size_t>, int> >	createInstructs;

  //3: LAUNCH CORE AND GRAPHICENGINE
  ClientCore	core(gameEntities, eventsHandler, createInstructs, connexionHandler);
  
  if (!core.initialize(options))
    return (EXIT_FAILURE);

  ThreadUI	threadUI(eventsHandler, gameEntities, createInstructs);
  core.run();

  //TODO: add failure condition to return correct value

  //threadUI.join();
  return (EXIT_SUCCESS);
}
