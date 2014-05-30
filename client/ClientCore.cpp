//
// ClientCore.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu May 29 15:44:40 2014 aurelien prieur
// Last update Fri May 30 15:18:42 2014 aurelien prieur
//

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

bool	ClientCore::initialize()
{
  _createInstructs.push(std::pair<std::pair<size_t, size_t>, ObjectType>(std::pair<size_t, size_t>(0,0), PLAYER));
  // if (!_gameEntities.addEntity(std::pair<size_t, size_t>(0, 0), PLAYER))
  //   return (false);
  return (true);
}
