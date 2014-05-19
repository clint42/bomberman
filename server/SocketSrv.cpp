//
// SocketSrv.cpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May 19 17:15:59 2014 julie franel
// Last update Mon May 19 17:28:47 2014 julie franel
//

#include "SocketSrv.hpp"

/*
** CONSTRUCTOR / DESTRUCTOR
*/

SocketSrv::SocketSrv(int port)
{
  this->getProtocol("TCP");
  this->openSocket();
  this->getPort(port);
  this->_sin.sin_family = AF_INET;
  this->getInetAddr("");
  this->bindSocket();
  this->listenSocket();
}

SocketSrv::~SocketSrv()
{

}


/*
** MEMBER FUNCTIONS
*/

void	SocketSrv::bindSocket()
{
  if (bind(this->_fd, (const struct sockaddr *)&(this->_sin), sizeof(this->_sin)) == -1)
    throw SocketException("Could not bind socket");
}

void	SocketSrv::listenSocket()
{
  if (listen(this->_fd, 5) == -1)
    throw SocketException("Could not listen socket");
}

void	SocketSrv::getInetAddr(const std::string &ip)
{
  (void)ip;
  this->_sin.sin_addr.s_addr = INADDR_ANY;
}
