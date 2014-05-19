/*
** Select.cpp for Select in /home/lafitt_g/Tek2/c++/bomberman/common
** 
** Made by lafitt_g
** Login   <lafitt_g@lafittg>
** 
** Started on  Mon May 19 15:13:01 2014 lafitt_g
** Last update Mon May 19 16:03:55 2014 lafitt_g
*/

#include "Select.hpp"

Select::Select()
{
}

Select::~Select()
{
}

void
Select::fdZeroRead()
{
  FD_ZERO(&this->_readfd);
}

void
Select::fdZeroWrite()
{
  FD_ZERO(&this->_writefd);
}

void
Select::fdSetRead(int fd)
{
  FD_SET(fd, &this->_readfd);
}

void
Select::fdSetWrite(int fd)
{
  FD_SET(fd, &this->_writefd);
}

int
Select::fdIssetRead(int fd)
{
  return (FD_ISSET(fd, &this->_readfd));
}

int
Select::fdIssetWrite(int fd)
{
  return (FD_ISSET(fd, &this->_writefd));
}

int
Select::fdSelect(int nfds, fd_set *exceptfds, struct timeval *timeout)
{
  return (select(nfds, &this->_readfd, &this->_writefd, exceptfds, timeout));
}
