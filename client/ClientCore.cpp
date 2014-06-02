//
// ClientCore.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu May 29 15:44:40 2014 aurelien prieur
// Last update Sat May 31 16:10:00 2014 aurelien prieur
//

#include <iostream>
#include "ClientCore.hpp"

ClientCore::ClientCore(GameEntities &gameEntities, EventsHandler &eventsHandler,
		       SafeQueue<std::pair<std::pair<size_t, size_t>, ObjectType> > &createInstructs):
  _gameEntities(gameEntities),
  _eventsHandler(eventsHandler),
  _createInstructs(createInstructs)
{
}

ClientCore::~ClientCore()
{
}

bool		ClientCore::initialize()
{
  _createInstructs.push(std::pair<std::pair<size_t, size_t>, ObjectType>(std::pair<size_t, size_t>(0,0), PLAYER));
  return (true);
}

bool		ClientCore::run()
{
  std::pair<size_t, size_t> coord(0, 0);
  EventsHandler::keyStatus	ks;

  while (_eventsHandler.getInputStatus(SDLK_ESCAPE) == NONE)
    {
      if ((ks = _eventsHandler.getInputStatus(SDLK_LEFT)) != NONE)
	{
	  std::cout << "LEFT: " << ks << std::endl; 
	}
      else if ((ks = _eventsHandler.getInputStatus(SDLK_RIGHT)) != NONE)
	{
	  std::cout << "RIGHT: " << ks << std::endl;
	}
      else if ((ks = _eventsHandler.getInputStatus(SDLK_UP)) != NONE)
	{
	  std::cout << "UP: " << ks << std::endl;
	}
      else if ((ks = _eventsHandler.getInputStatus(SDLK_DOWN)) != NONE)
	{
	  std::cout << "DOWN: " << ks << std::endl;
	}
    }
}
