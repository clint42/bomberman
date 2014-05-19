//
// ThreadUI.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 17:19:12 2014 aurelien prieur
// Last update Mon May 19 15:01:35 2014 aurelien prieur
//

#include "ThreadUI.hpp"

ThreadUI::ThreadUI(GameEntities &gameEntities): _gameEntities(gameEntities)
{
  if (pthread_create(&_thread, 0, ThreadUI::threadLaunch, static_cast<void *>(this)) != 0)
    throw ThreadException("Unable to launch thread");
}

ThreadUI::~ThreadUI()
{
}

void		*ThreadUI::threadLaunch(void *thread)
{
  ThreadUI	*pthread;

  pthread = static_cast<ThreadUI *>(thread);
  pthread->run();
  return (NULL);
}

void		*ThreadUI::run()
{
  UI		ui(_gameEntities);

  if (!ui.run())
    {
      //RETURN ERROR
    }
  //RETURN SUCCESS
  return (NULL);
}

bool		ThreadUI::join()
{
  if (pthread_join(_thread, NULL) != 0)
    throw ThreadException("Unable to join thread");
  return (true);
}

ThreadException::ThreadException(std::string const &what): _what(what)
{
}

ThreadException::~ThreadException() throw()
{
}

const char	*ThreadException::what() const throw()
{
  return (_what.c_str());
}
