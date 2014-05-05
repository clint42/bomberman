#include "Exception.hh"

ABombermanException::ABombermanException(std::string const &msg) throw() : _message(msg) {}
ABombermanException::~ABombermanException(void) throw() {}
std::string const &
ABombermanException::message(void) const throw()
{
  return this->_message;
}

Md5Exception::Md5Exception(void) throw() : ABombermanException("Couldn't open the map") {}
Md5Exception::~Md5Exception(void) throw() {}
