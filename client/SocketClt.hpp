//
// SocketClt.hpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May 19 16:01:46 2014 julie franel
// Last update Mon May 19 17:11:29 2014 julie franel
//

#ifndef		SOCKETCLT_HPP_
# define	SOCKETCLT_HPP_

# include	"ASocket.hpp"

class		SocketClt : public ASocket
{
  void		connectSocket();
  virtual void	getInetAddr(const std::string &ip);

public:
  SocketClt(const std::string &ip, int port);
  ~SocketClt();
};

#endif		/* !SOCKETCLT_HPP_ */
