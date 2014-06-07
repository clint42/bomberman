//
// Poll.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/common
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Tue May 20 09:31:20 2014 aurelien prieur
// Last update Fri Jun  6 15:18:17 2014 buret_j
//

#ifndef POLL_HPP_
# define POLL_HPP_

# include <iostream>
# include <string>
# include <vector>
# include <poll.h>
# include <exception>


class	PollException: std::exception
{
  std::string	const _what;
public:
  PollException(std::string const &what);
  ~PollException() throw();
  const char	*what() const throw();
};

class	Poll
{
  std::vector<struct pollfd>	_fds;
public:
  Poll();
  ~Poll();
  void		watchEvent(int fd, int event);
  void		stopWatchingEvent(int fd, int event = (POLLIN | POLLOUT));
  inline void	disconnected(int fd) { stopWatchingEvent(fd, POLLIN | POLLOUT | POLLRDHUP); }
  bool		isEventOccurred(int fd, int event);
  bool		isDisconnected(int fd);
  int		pollFn(int timeout);
};


#endif // !POLL_HPP_
