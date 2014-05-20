//
// Poll.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/common
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Tue May 20 09:31:20 2014 aurelien prieur
// Last update Tue May 20 10:38:51 2014 aurelien prieur
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
  void	watchEvent(int fd, int event, bool revents);
  void	stopWatchingEvent(int fd, int event, bool revents);
  bool	isEventOccurred(int fd, int event, bool revents);
  int	pollFn(int timeout);
};


#endif // !POLL_HPP_
