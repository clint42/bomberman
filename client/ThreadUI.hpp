//
// ThreadUI.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 17:16:05 2014 aurelien prieur
// Last update Fri May 16 17:59:16 2014 aurelien prieur
//

#ifndef THREADUI_HPP_
# define THREADUI_HPP_

# include <pthread.h>
# include <string>
# include <exception>
# include "GameEntities.hpp"
# include "UI.hpp"

class	ThreadUI
{
  pthread_t	_thread;
  GameEntities	*_gameEntities;
  static void	*threadLaunch(void *);
  void		*run();
public:
  Thread(GameEntities *gameEntities);
  virtual ~Thread();
  bool		join();
};

class	ThreadException: public std::exception
{
  std::string	_what;
public:
  ThreadException(std::string const &what);
  ~ThreadException() throw();
  const char	*what() const throw();
};

#endif // !THREADUI_HPP_
