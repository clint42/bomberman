/*
// ConnexionHandler.cpp for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Mon May 26 15:06:00 2014 buret_j
** Last update Sat Jun  7 20:01:01 2014 lafitt_g
*/

#include "ConnexionHandler.hpp"

ConnexionHandler::Server *
ConnexionHandler::server(int port) {
  if (!_server && !_client) { _server = new Server(port); }
  _poll.watchEvent(server()->getMasterSocket()->getFd(), POLLIN);
  return _server;
}

ConnexionHandler::Client *
ConnexionHandler::client(int port, std::string const &ip) {
  if (!_client && !_server)
    _client = new Client(port, ip);
  return _client;
}

void
ConnexionHandler::reset() {
  delete _server;
  _server = NULL;
  delete _client;
  _client = NULL;
}

void
ConnexionHandler::rmSocket(Socket *s) {
  try {
    _poll.disconnected(s->getFd());
  } catch (PollException) { }
  if (_server)
    _server->rmSocket(s);
}

void
ConnexionHandler::perform(void (*fct)(void *, Socket *, bool b[3]), void *param) {
  if (this->server() != NULL)
    _server->perform(fct, param, &_poll);
  else if (this->client() != NULL)
    _client->perform(fct, param, &_poll);
}

Socket *
ConnexionHandler::getMasterSocket() {
  if (this->server() != NULL)
    return _server->getMasterSocket();
  else if (this->client() != NULL)
    return _client->getMasterSocket();
  return (NULL);
}

/*
** <-- main
** server -->
*/

ConnexionHandler::Server::Server(int p) : _masterSocket(0), _port(p) {
  this->initialise();
}

void
ConnexionHandler::Server::initialise() {
  if (_masterSocket)
    throw ConnexionException("Server already initialised");

  int		fd = socket(PF_INET, SOCK_STREAM, 0);
  sockaddr_in	sin;

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(_port);
  if (fd == -1
      || bind(fd, (sockaddr*)&sin, sizeof sin) == -1
      || listen(fd, 10) == -1)
    throw ConnexionException("Can't create socket properly");
  _sockets[fd] = new Socket(fd);
  _masterSocket = _sockets[fd];
}

ConnexionHandler::Server::~Server() {
  for (std::vector<Socket *>::iterator it = _sockets.begin();
       it != _sockets.end(); ++it) {
    delete (*it);
  }
}

void
ConnexionHandler::Server::acceptPeer(Poll *poll, void *srv) {
  sockaddr_in	sin;
  socklen_t     sin_len;
  int		fd;

  (void)srv;
  fd = accept(_masterSocket->getFd(), (sockaddr *)&sin, &sin_len);
  _sockets[fd] = new Socket(fd);
  poll->watchEvent(fd, POLLIN);
  poll->watchEvent(fd, POLLOUT);
  // ((Server::Server *)srv)->addPeer(_sockets[fd]);
}

void
ConnexionHandler::Server::perform(void (*fct)(void *, Socket *, bool b[3]),
				  void *param, Poll *poll) {
  bool	event[3];

  for (std::vector<Socket *>::iterator it = _sockets.begin();
       it != _sockets.end(); ++it) {
    
    event[0] = poll->isEventOccurred((*it)->getFd(), POLLIN);
    event[1] = poll->isEventOccurred((*it)->getFd(), POLLOUT);
    event[2] = poll->isDisconnected((*it)->getFd());
    if (event[0] || event[1] || event[2]) {
      if (_masterSocket && *it == _masterSocket)
	this->acceptPeer(poll, param);
      else
	fct(param, *it, event);
    }
  }
}

void
ConnexionHandler::Server::rmSocket(Socket *s) {
  if (_sockets[s->getFd()] != NULL) {
    _sockets[s->getFd()] = NULL;
    if (s == _masterSocket)
      _masterSocket = NULL;
    delete s;
  }
}

/* *****************
** <- Server
** Client ->
*/

ConnexionHandler::Client::Client(int port, std::string const &ip) {
  protoent *	pe = getprotobyname("TCP");
  int		fd = socket(PF_INET, SOCK_STREAM, pe->p_proto);
  sockaddr_in	sin;

  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(ip.c_str());
  if (!pe || fd == -1 || connect(fd, (sockaddr *)&sin, sizeof sin) == -1) throw ConnexionException("Can't create Client properly");
  _socket = new Socket(fd);
}

ConnexionHandler::Client::~Client() {
  delete _socket;
}

void
ConnexionHandler::Client::perform(void (*fct)(void *, Socket *, bool b[3]),
				  void *param,
				  Poll *poll) {
  bool	event[3];

  event[0] = poll->isEventOccurred(_socket->getFd(), POLLIN);
  event[1] = poll->isEventOccurred(_socket->getFd(), POLLOUT);
  event[2] = poll->isDisconnected(_socket->getFd());
  if (event[0] || event[1] || event[2])
    fct(param, _socket, event);
}
