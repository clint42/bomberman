//
// main.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 15:53:47 2014 aurelien prieur
// Last update Sat Jun  7 18:49:46 2014 aurelien prieur
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

int	main()
{
  srand(time(0));
  //Launch graphic thread
  ConnexionHandler	connexionHandler;
  EventsHandler		eventsHandler(connexionHandler);
  GameEntities		gameEntities;
  SafeQueue<std::pair<std::pair<size_t, size_t>, int> >	createInstructs;

  //1: LAUNCH MAIN MENU
  //2: LAUNCH SUB MENU (DEPENDING OF MAIN MENU RESULT)
  
  //3: LAUNCH CORE AND GRAPHICENGINE
  ThreadUI	threadUI(eventsHandler, gameEntities, createInstructs);
  ClientCore	core(gameEntities, eventsHandler, createInstructs, connexionHandler);

  core.initialize();
  core.run();
  //TODO: add failure condition to return correct value
  threadUI.join();
  return (EXIT_SUCCESS);
}
