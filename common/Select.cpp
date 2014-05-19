/*
** Select.cpp for Select in /home/lafitt_g/Tek2/c++/bomberman/common
** 
** Made by lafitt_g
** Login   <lafitt_g@lafittg>
** 
** Started on  Mon May 19 15:13:01 2014 lafitt_g
// Last update Mon May 19 17:44:17 2014 aurelien prieur
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
  _maxfd = 0;
  FD_ZERO(&this->_readfd);
}

void
Select::fdZeroWrite()
{
  _maxfd = 0;
  FD_ZERO(&this->_writefd);
}

void
Select::fdSetRead(int fd)
{
  _maxfd = (fd > _maxfd) ? fd : _maxfd;
  FD_SET(fd, &this->_readfd);
}

void
Select::fdSetWrite(int fd)
{
  _maxfd = (fd > _maxfd) ? fd : _maxfd;
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
Select::fdSelect(struct timeval *timeout)
{
  return (select(_maxfd + 1, &this->_readfd, &this->_writefd, NULL, timeout));
}
