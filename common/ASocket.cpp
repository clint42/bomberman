//
// ASocket.cpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May 19 13:29:57 2014 julie franel
// Last update Mon May 19 15:55:22 2014 julie franel
//

#include "ASocket.hpp"

/*
** CONSTRUCTOR / DESTRUCTOR
*/

ASocket::ASocket(void)
{

}

ASocket::~ASocket(void)
{

}


/*
** MEMBER FUNCTIONS
*/

void	ASocket::getProtocol(const std::string &name)
{
  if ((this->_pe = getprotobyname(name.c_str())) == NULL)
    throw SocketException("Could not get protocole by name");
}

void	ASocket::openSocket(void)
{
  if ((this->_fd = socket(AF_INET, SOCK_STREAM, this->_pe->p_proto)) == -1)
    throw SocketException("Could not open sokcet master");
}

void	ASocket::getPort(int port)
{
  this->_sin.sin_port = htons(port);
}
