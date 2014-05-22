//
// ConnexionHandler.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Thu May 22 15:28:06 2014 buret_j
// Last update Thu May 22 17:48:56 2014 buret_j
//

#ifndef CONNEXIONHANDLER_HPP_
# define CONNEXIONHANDLER_HPP_

# include <netinet/in.h>
# include <sys/types.h>
# include <sys/socket.h>

# include "Socket.hpp"

class	ConnexionHandler {

public:

  class Server;
  class Client;
  
private:

  Server *	_server;
  Client *	_client;
  
public:

  Client() {}
  ~Client() {}

  inline Server *	Server() { return _server; }
  inline Server *	Server(int port) {
    if (!_server && !_client) _server = new Server;
    return _server;
  }

  inline Client *	Client() { return _client; }
  inline Client *	Client(int port, std::string const &ip) { 
    if (!_client && !_server) _client = new Client(port, ip);
    return _client;
  }


public: // nested classes definition

  class Server {

    /* Note:
     *   The first `Socket*' from the `list' corresponds to the 'Master Socket'
     */
    std::list<Socket *> _sockets;
    size_t		_biggestFd;

    inline void	updateBiggestFd(size_t fd) {
      if (fd == _biggestFd) { // c'est qu'il est rm. Faut trouver l'autre plus grand
	;
      } else if (fd > _biggestFd) // c'est qu'il est add
	_biggestFd = fd;
    }

  public:

    Server(int p) {
      int		fd = socket(PF_INET, SOCK_STREAM, 0);
      sockaddr_in	sin;

      _biggestFd = 2;
      sin.sin.sin_addr.s_addr = htonl(INADDR_ANY);
      sin.sin_family = AF_INET;
      sin.sin_port = htons(p);
      if (fd == -1
	  || bind(fd, (sockaddr*)&sin, sizeof serveur->sin) == -1
	  || listen(fd, 10) == -1)
	throw ConnexionException;
      _socket.push_back(new Socket(fd));
      updateBiggestFd(fd);
    }
    ~Server() {}

  }; // !Server

  class Client {
    Socket *_socket;

    Client(int port, std::string const &ip) {
      protoent *	pe = getprotobyname("TCP");
      int		fd = socket(PF_INET, SOCK_STREAM, pe);
      sockaddr_in	sin;

      if (!pe || fd == -1) throw ConnexionException;
      sin.sin_family = AF_INET;
      sin.sin_port = htons(port);
      sin.sin_addr.s_addr = inet_addr(ip.c_str());
      connect(fd);
      _socket = new Socket(fd);
    }
    ~Client() {}
    

  }; // !Client

};

#endif
