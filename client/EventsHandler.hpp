//
// EventsHandler.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu May 29 15:57:53 2014 aurelien prieur
// Last update Mon Jun  2 13:19:52 2014 aurelien prieur
//

#ifndef EVENTSHANDLER_HPP_
# define EVENTSHANDLER_HPP_

# include <Input.hh>
# include <vector>
# include <utility>
# include "Mutex.hpp"

# define SDLK_LAST 323

class		EventsHandler
{
  gdl::Input		_last;
  gdl::Input		*_current;
  std::ostringstream	_bufOut;
  Mutex			_mutex;
  Condvar		_condVar;

public:
  enum	keyStatus
    {
      DOWN,
      HOLD,
      UP,
      NONE
    };
  EventsHandler();
  ~EventsHandler();
  keyStatus		getInputStatus(int input);
  void			setEvents(gdl::Input last);
  void			initialize(gdl::Input *inputs);
  void			signal(void);
  void			wait(void);
};

#endif // !EVENTHANDLER_HPP_
