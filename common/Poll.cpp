//
// Poll.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/common
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Tue May 20 09:42:06 2014 aurelien prieur
// Last update Mon Jun  9 14:16:49 2014 buret_j
//

#include <iostream>
#include "Poll.hpp"

Poll::Poll()
{
}

Poll::~Poll()
{
}

void		Poll::watchEvent(int fd, int event)
{
  size_t	i;

  i = 0;
  while (i < _fds.size())
    {
      if (_fds[i].fd == fd)
	{
	  _fds[i].events |= event;
	  _fds[i].revents = 0;
	  return ;
	}
      ++i;
    }
  _fds.resize(_fds.size() + 1);
  _fds[i].fd = fd;
  _fds[i].events |= event | POLLRDHUP | POLLHUP;
  _fds[i].revents = 0;
} 

void		Poll::stopWatchingEvent(int fd, int event)
{
  for (std::vector<struct pollfd>::iterator it = _fds.begin();
       it != _fds.end(); ++it)
    {
      if (it->fd == fd)
	{
	  it->events &= ~event;
	  if (it->events == 0 && it->revents == 0)
	    _fds.erase(it);
	  return ;
	}
    }
  throw PollException("fd not set");
}

bool		Poll::isEventOccurred(int fd, int event)
{
  static size_t	lastCheck = 0;
  
  if (_fds[lastCheck].fd == fd)
    return ((_fds[lastCheck].revents & event) == event);
  for (size_t i = 0; i < _fds.size(); ++i)
    {
      if (_fds[i].fd == fd)
	{
	  lastCheck = i;
	  return ((_fds[i].revents & event) == event);
	}
    }
  throw PollException("fd not set");
}

bool		Poll::isDisconnected(int fd)
{
  // DEBUG("Poll::isDisconnected", 1);
  for (size_t i = 0; i < _fds.size(); ++i)
    {
      if (_fds[i].fd == fd)
	{
	  // DEBUG("! Poll::isDisconnected", -1);
	  return ((_fds[i].revents & (POLLRDHUP | POLLHUP)));
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

