//
// ThreadUI.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 17:16:05 2014 aurelien prieur
// Last update Wed Jun  4 17:41:26 2014 aurelien prieur
//

#ifndef THREADUI_HPP_
# define THREADUI_HPP_

# include <pthread.h>
# include <string>
# include <exception>
# include "GameEntities.hpp"
# include "EventsHandler.hpp"
# include "UI.hpp"
# include "ThreadException.hpp"
# include "SafeQueue.hpp"

class	ThreadUI
{
  pthread_t	_thread;
  EventsHandler	&_eventsHandler;
  GameEntities	&_gameEntities;
  SafeQueue<std::pair<std::pair<size_t, size_t>, int> >	&_createInstructs;
  static void	*threadLaunch(void *);
  void		*run();

public:
  ThreadUI(EventsHandler &eventsHandler,
	   GameEntities &gameEntities,
	   SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs);
  virtual ~ThreadUI();
  bool		join();
  GameEntities	&getGameEntities();
};

#endif // !THREADUI_HPP_
