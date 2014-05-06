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

SizeException::SizeException(void) throw(): ABombermanException("Map size must be equal to 4*4 or higher") {}
SizeException::~SizeException(void) throw() {}
