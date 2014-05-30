//
// EventsHandler.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu May 29 16:01:34 2014 aurelien prieur
// Last update Thu May 29 17:49:56 2014 aurelien prieur
//

#include "EventsHandler.hpp"

EventsHandler::EventsHandler()
{
  _lastEvents.resize(SDLK_LAST);
  _currentEvents.resize(SDLK_LAST);
  for (int i = 0; i < SDLK_LAST; ++i)
    {
      _lastEvents[i] = false;
      _currentEvents[i] = false;
    }
}

EventsHandler::~EventsHandler()
{
}

bool	EventsHandler::getKeyReleased(int input)
{
  if (_lastEvents[input] && !_currentEvents[input])
    {
      _lastEvents[input] = false;
      return (true);
    }
  return (false);
}

void	EventsHandler::clearEvents()
{
  for (int i = 0; i < SDLK_LAST; ++i)
    {
      _currentEvents[i] = false;
      _lastEvents[i] = false;
    }
}
