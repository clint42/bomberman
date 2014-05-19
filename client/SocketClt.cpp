//
// SocketClt.cpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May 19 16:06:46 2014 julie franel
// Last update Mon May 19 17:11:05 2014 julie franel
//

#include "SocketClt.hpp"

/*
** CONSTRUCTOR / DESTRUCTOR
*/

SocketClt::SocketClt(const std::string &ip, int port)
{
  this->getProtocol("TCP");
  this->openSocket();
  this->_sin.sin_family = AF_INET;
  this->getPort(port);
  this->getInetAddr(ip);
  this->connectSocket();
}

SocketClt::~SocketClt()
{

}


/*
** MEMBER FUNCTIONS
*/

void	SocketClt::connectSocket()
{
  if (connect(this->_fd, (const struct sockaddr *)&(this->_sin), sizeof(this->_sin)) == -1)
    throw SocketException("Could not connect socket client");
}

void	SocketClt::getInetAddr(const std::string &ip)
{
  this->_sin.sin_addr.s_addr = inet_addr(ip.c_str());
}
