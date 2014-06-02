//
// main.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 15:53:47 2014 aurelien prieur
// Last update Sat May 31 15:23:24 2014 aurelien prieur
//

#include <unistd.h>
#include <iostream>
#include "GameEntities.hpp"
#include "EventsHandler.hpp"
#include "ThreadUI.hpp"
#include "ClientCore.hpp"
#include "SafeQueue.hpp"
#include "AObject.hpp"

int	main()
{
  //Launch graphic thread
  EventsHandler	eventsHandler;
  GameEntities	gameEntities;
  SafeQueue<std::pair<std::pair<size_t, size_t>, ObjectType> >	createInstructs;

  //1: LAUNCH MAIN MENU
  //2: LAUNCH SUB MENU (DEPENDING OF MAIN MENU RESULT)
  
  //3: LAUNCH CORE AND GRAPHICENGINE
  ThreadUI	threadUI(eventsHandler, gameEntities, createInstructs);
  ClientCore	core(gameEntities, eventsHandler, createInstructs);

  core.initialize();
  // core.play();
  // core.end();
  //TODO: add failure condition to return correct value
  threadUI.join();
  return (EXIT_SUCCESS);
}
