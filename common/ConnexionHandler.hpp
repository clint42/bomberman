//
// ConnexionHandler.hpp for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Thu May 22 15:28:06 2014 buret_j
// Last update Thu Jun  5 18:46:37 2014 buret_j
//

#ifndef CONNEXIONHANDLER_HPP_
# define CONNEXIONHANDLER_HPP_

# include <netdb.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>

# include <vector>

# include "Exception.hpp"
# include "Socket.hpp"
# include "Poll.hpp"

class	ConnexionHandler {

public:

  class Server;
  class Client;

private:

  Server *	_server;
  Client *	_client;
  Poll		_poll;

public:

  ConnexionHandler() {}
  ~ConnexionHandler() {}

  inline Server *	server() { return _server; }
  Server *		server(int port);
  inline Client *	client() { return _client; }
  Client *		client(int port, std::string const &ip);

  void			reset();
  void			rmSocket(Socket *s);

  void			perform(void (*fct)(void *, Socket *, bool b[3]), void *param);

  Socket *		getMasterSocket();

  inline void		watchEventOnSocket(Socket *s, int e) { _poll.watchEvent(s->getFd(), e); }
  inline void	        unwatchEventOnSocket(Socket *s, int e) {_poll.stopWatchingEvent(s->getFd(), e);}

  inline int		update(int t) { return _poll.pollFn(t); }

public: // nested classes definition

  class Server {
    std::vector<Socket *> _sockets;
    Socket *		  _masterSocket;
    int			  _port;

    void	acceptPeer(Poll *, void *srv);

  public:
    Server(int p);
    ~Server();

    void		initialise();
    void		perform(void (*fct)(void *, Socket *, bool b[3]), void *param, Poll *poll);
    inline Socket *	getMasterSocket() { return _masterSocket; }
    void	        rmSocket(Socket *s);
  }; // !Server


  class Client {
    Socket *	_socket;

  public:
    Client(int port, std::string const &ip);
    ~Client();

    void		perform(void (*fct)(void *, Socket *, bool b[3]), void *param, Poll *poll);
    inline Socket *	getMasterSocket() { return _socket; }
    
  }; // !Client

};

#endif
