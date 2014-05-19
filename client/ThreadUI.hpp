//
// ThreadUI.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 17:16:05 2014 aurelien prieur
// Last update Mon May 19 15:00:03 2014 aurelien prieur
//

#ifndef THREADUI_HPP_
# define THREADUI_HPP_

# include <pthread.h>
# include <string>
# include <exception>
# include "GameEntities.hpp"
# include "UI.hpp"
# include "ThreadException.hpp"

class	ThreadUI
{
  pthread_t	_thread;
  GameEntities	&_gameEntities;
  static void	*threadLaunch(void *);
  void		*run();
public:
  ThreadUI(GameEntities &gameEntities);
  virtual ~ThreadUI();
  bool		join();
};

#endif // !THREADUI_HPP_
