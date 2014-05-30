//
// ClientCore.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu May 29 15:42:09 2014 aurelien prieur
// Last update Fri May 30 15:12:46 2014 aurelien prieur
//

#ifndef CLIENTCORE_HPP_
# define CLIENTCORE_HPP_

# include <utility>
# include "GameEntities.hpp"
# include "EventsHandler.hpp"
# include "SafeQueue.hpp"

class		ClientCore
{
  GameEntities	&_gameEntities;
  EventsHandler	&_eventsHandler;
  SafeQueue<std::pair<std::pair<size_t, size_t>, ObjectType> > &_createInstructs;
public:
  ClientCore(GameEntities &gameEntities, EventsHandler &eventsHandler,
	     SafeQueue<std::pair<std::pair<size_t, size_t>, ObjectType> > &createInstructs);
  ~ClientCore();
  bool		initialize();
};

#endif // !CLIENTCORE_HPP_
