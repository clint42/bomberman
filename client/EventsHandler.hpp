//
// EventsHandler.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu May 29 15:57:53 2014 aurelien prieur
// Last update Thu May 29 17:49:07 2014 aurelien prieur
//

#ifndef EVENTSHANDLER_HPP_
# define EVENTSHANDLER_HPP_

# include <SdlContext.hh>
# include <vector>
# include <utility>
# include "Mutex.hpp"

# define SDLK_LAST 323

class			EventsHandler
{
  std::vector<bool>	_lastEvents;	
  std::vector<bool>	_currentEvents;
  Mutex			_mutex;
public:
  EventsHandler();
  ~EventsHandler();
  bool			getKeyReleased(int input);
  void			clearEvents();
};

#endif // !EVENTHANDLER_HPP_
