//
// SocketSrv.hpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May 19 17:13:17 2014 julie franel
// Last update Wed May 21 16:57:52 2014 julie franel
//

#ifndef		SOCKETSRV_HPP_
# define	SOCKETSRV_HPP_

# include	<map>
# include	"ASocket.hpp"

class		SocketSrv : public ASocket
{
  void		bindSocket();
  void		listenSocket();
  virtual void	getInetAddr(const std::string &ip);
  void		createSocketMaster(int port);
  void		createSocketClient(int port);

public:
  typedef void	(SocketSrv::*createSocket)(int port);
  enum socketType
    {
      MASTER,
      CLIENT
    };

  SocketSrv(int port, socketType type);
  ~SocketSrv();
};

#endif		/* !SOCKETSRV_HPP_ */
