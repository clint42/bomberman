//
// SocketSrv.cpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May 19 17:15:59 2014 julie franel
// Last update Wed May 21 18:13:01 2014 julie franel
//

#include "SocketSrv.hpp"

/*
** CONSTRUCTOR / DESTRUCTOR
*/

SocketSrv::SocketSrv(int port, socketType type)
{
  std::map<socketType, createSocket>	typePtr;

  typePtr[MASTER] = &SocketSrv::createSocketMaster;
  typePtr[CLIENT] = &SocketSrv::createSocketClient;
  (this->*typePtr[type])(port);
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

void	SocketSrv::createSocketMaster(int port)
{
  this->getProtocol("TCP");
  this->openSocket();
  this->getPort(port);
  this->_sin.sin_family = AF_INET;
  this->getInetAddr("");
  this->bindSocket();
  this->listenSocket();
  std::cout << "Socket master" << std::endl;
}

void	SocketSrv::createSocketClient(int port)
{
  (void)port;
  std::cout << "Socket client" << std::endl;
}
