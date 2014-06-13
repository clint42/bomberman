//
// Exception.cpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Tue May  6 11:18:51 2014 julie franel
// Last update Fri Jun 13 15:16:07 2014 julie franel
//

#include "Exception.hpp"

ABombermanException::ABombermanException(std::string const &msg) throw() : _message(msg) {}
ABombermanException::~ABombermanException(void) throw() {}
const char
*ABombermanException::what(void) const throw()
{
  return this->_message.c_str();
}
