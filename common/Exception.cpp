//
// Exception.cpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Tue May  6 11:18:51 2014 julie franel
// Last update Tue Jun  3 15:40:58 2014 buret_j
//

#include "Exception.hpp"

ABombermanException::ABombermanException(std::string const &msg) throw() : _message(msg) {}
ABombermanException::~ABombermanException(void) throw() {}
std::string const &
ABombermanException::message(void) const throw()
{
  return this->_message;
}

Md5Exception::Md5Exception(void) throw() : ABombermanException("Couldn't open the map") {}
Md5Exception::~Md5Exception(void) throw() {}

MapException::MapException(const std::string &msg) throw(): ABombermanException(msg) {}
MapException::~MapException(void) throw() {}

SocketException::SocketException(const std::string &msg) throw(): ABombermanException(msg) {}
SocketException::~SocketException(void) throw() {}

ServerException::ServerException(const std::string &msg) throw(): ABombermanException(msg) {}
ServerException::~ServerException(void) throw() {}

ConnexionException::ConnexionException(const std::string &m) throw() : ABombermanException(m) {}
ConnexionException::~ConnexionException() throw() {}
