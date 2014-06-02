//
// ConnexionHandler.hpp for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Thu May 22 15:28:06 2014 buret_j
// Last update Mon Jun  2 18:37:36 2014 aurelien prieur
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

  inline Server *	Server(int port) {
    if (!_server && !_client) { _server = new Server(port); }
    _poll.watchEvent(Server()->getMasterSocket(), POLLIN);
    return _server;
  }
  inline Server *	Server() { return _server; }

  inline Client *	Client() { return _client; }
  inline Client *	Client(int port, std::string const &ip) {
    if (!_client && !_server) _client = new Client(port, ip);
    return _client;
  }

  inline void		reset() {
    delete _server; _server = NULL;
    delete _client; _client = NULL;
  }

  inline void		rmSocket(Socket *s) {
    if (_sockets[s->getFd()] != NULL) {
      _sockets[s->getFd()] = NULL;
      delete s;
    }
  }

  inline void	        perform(void (*fct)(void *, Socket *, bool b[3]), void *param) {
    if (this->Server() != NULL)
      _server->perform(fct, param, &_poll);
    else if (this->Client() != NULL)
      _client->perform(fct, param, &_poll);
  }

  inline Socket *	getMasterSocket() const {
    if (this->Server() != NULL)
      _server->getMasterSocket();
    else if (this->Client() != NULL)
      _client->getMasterSocket();
    return (NULL);
  }

  inline void		watchEventOnSocket(Socket *s, int e) { _poll.watchEvent(s->getFd(), e); }
  inline void	        unwatchEventOnSocket(Socket *s, int e) {_poll.stopWatchingEvent(s->getFd(), e);}

  inline int		update(int t) { return _poll.pollFn(t); }

public: // nested classes definition

  class Server {
    std::vector<Socket *> _sockets;
    int			  _masterSocket;

    void	accept();

  public:
    Server(int p);
    ~Server();

    void		perform(void (*fct)(void *, Socket *, bool b[3]), void *param, Poll *poll);
    inline Socket *	getMasterSocket() const { return _masterSocket; }
  }; // !Server


  class Client {
    Socket *	_socket;

  public:
    Client(int port, std::string const &ip);
    ~Client();

    void		perform(void (*fct)(void *, Socket *, bool b[3]), void *param, Poll *poll);
    inline Socket *	getMasterSocket() const { return _socket; }
  }; // !Client

};

#endif
