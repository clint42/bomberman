//
// ConnexionHandler.cpp for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Mon May 26 15:06:00 2014 buret_j
// Last update Fri May 30 12:05:01 2014 julie franel
//

#include "ConnexionHandler.hpp"

ConnexionHandler::Server::Server(int p) {
  int		fd = socket(PF_INET, SOCK_STREAM, 0);
  sockaddr_in	sin;

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(p);
  if (fd == -1
      || bind(fd, (sockaddr*)&sin, sizeof serveur->sin) == -1
      || listen(fd, 10) == -1)
    throw ConnexionException;
  _sockets[fd] = new Socket(fd);
  _masterSocket = fd;
}

ConnexionHandler::Server::~Server() {
  for (std::vector<Socket *>::iterator it = _sockets.begin();
       it != _sockets.end(); ++it) {
    delete (*it);
  }
}

void
ConnexionHandler::Server::accept() {
  sockaddr_in	sin;
  socklen_t     sin_len;
  int		fd;
  Socket *	socket;

  fd = accept(s->sockfd, (sockaddr *)&sin, &sin_len);
  socket = new Socket(fd)
  _sockets.push_back(socket);
  _poll.watchEvent(fd, POLLIN);
  _poll.watchEvent(fd, POLLOUT);
}

void
ConnexionHandler::Server::perform(void (*fct)(void *, Socket *, bool b[3]),
				  void *param,
				  Poll *poll) {
  bool	event[3];

  for (std::vector<Socket *>::iterator it = _sockets.begin();
       it != _sockets.end(); ++it) {
    if ((*it)->getFd() == _masterSocket)
      this->accept();
    else {
      event[0] = poll->isEventOccured((*it)->getFd(), POLLIN);
      event[1] = poll->isEventOccured((*it)->getFd(), POLLOUT);
      event[2] = poll->isDisconnected((*it)->getFd());
      if (event[0] || event[1] || event[2])
	fct(param, *it, event);
    }
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
  if (!pe || fd == -1 || connect(fd) == -1) throw ConnexionException;
  _socket = new Socket(fd);
}

ConnexionHandler::Client::~Client() {
}

void
ConnexionHandler::Client::perform(void (*fct)(void *, Socket *, bool b[3]),
				  void *param,
				  Poll *poll) {
  bool	event[3];

  event[0] = poll->isEventOccured(_socket->getFd(), POLLIN);
  event[1] = poll->isEventOccured(_socket->getFd(), POLLOUT);
  event[2] = poll->isDisconnected(_socket->getFd());
  if (event[0] || event[1] || event[2])
    fct(param, *it, event);
}
