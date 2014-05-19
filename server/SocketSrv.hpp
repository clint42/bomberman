//
// SocketSrv.hpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May 19 17:13:17 2014 julie franel
// Last update Mon May 19 17:28:20 2014 julie franel
//

#ifndef		SOCKETSRV_HPP_
# define	SOCKETSRV_HPP_

# include	"ASocket.hpp"

class		SocketSrv : public ASocket
{
  void		bindSocket();
  void		listenSocket();
  virtual void	getInetAddr(const std::string &ip);

public:
  SocketSrv(int port);
  ~SocketSrv();
};

#endif		/* !SOCKETSRV_HPP_ */
