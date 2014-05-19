//
// ASocket.hpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May 19 11:08:18 2014 julie franel
// Last update Mon May 19 17:05:56 2014 julie franel
//

#ifndef			ASOCKET_HPP_
# define		ASOCKET_HPP_

# include		<iostream>
# include		<string>
# include		<netdb.h>
# include		<sys/types.h>
# include		<sys/socket.h>
# include		<arpa/inet.h>
# include		<netinet/in.h>
# include		"Exception.hpp"

class			ASocket
{
protected:
  int			_fd;
  struct protoent	*_pe;
  struct sockaddr_in	_sin;

  void			getProtocol(const std::string &name);
  void			openSocket(void);
  void			getPort(int port);
  virtual void		getInetAddr(const std::string &ip) = 0;

public:
  ASocket(void);
  virtual ~ASocket(void);
};

#endif			/* !ASOCKET_HPP_ */
