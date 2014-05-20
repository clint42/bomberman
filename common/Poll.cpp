//
// Poll.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/common
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Tue May 20 09:42:06 2014 aurelien prieur
// Last update Tue May 20 10:46:02 2014 aurelien prieur
//

#include "Poll.hpp"

Poll::Poll()
{
}

Poll::~Poll()
{
}

void		Poll::watchEvent(int fd, int event, bool revents)
{
  size_t	i;

  i = 0;
  while (i < _fds.size())
    {
      if (_fds[i].fd == fd)
	{
	  if (!revents)
	    _fds[i].events |= event;
	  else
	    _fds[i].revents |= event;
	  return ;
	}
      ++i;
    }
  _fds.resize(1);
  _fds[i].fd = fd;
  if (!revents)
    _fds[i].events = event;
  else
    _fds[i].revents = event;
} 

void		Poll::stopWatchingEvent(int fd, int event, bool revents)
{
  for (std::vector<struct pollfd>::iterator it = _fds.begin();
       it != _fds.end(); ++it)
    {
      if (it->fd == fd)
	{
	  if (!revents)
	    it->events &= ~event;
	  else
	    it->revents &= ~event;
	  if (it->events == 0 && it->revents == 0)
	    _fds.erase(it);
	  return ;
	}
    }
  throw PollException("fd not set");
}

bool		Poll::isEventOccurred(int fd, int event, bool revents)
{
  for (size_t i = 0; i < _fds.size(); ++i)
    {
      if (_fds[i].fd == fd)
	{
	  if (!revents)
	    return ((_fds[i].events & event) == event);
	  else
	    return ((_fds[i].revents & event) == event);
	}
    }
  throw PollException("fd not set");
}

int		Poll::pollFn(int timeout)
{
  return (poll(&_fds[0], _fds.size(), timeout));
}

PollException::PollException(std::string const &what): _what(what)
{
}

PollException::~PollException() throw()
{
}

const char	*PollException::what() const throw()
{
  return (_what.c_str());
}
