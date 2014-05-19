/*
** Select.cpp for Select in /home/lafitt_g/Tek2/c++/bomberman/common
** 
** Made by lafitt_g
** Login   <lafitt_g@lafittg>
** 
** Started on  Mon May 19 15:13:01 2014 lafitt_g
// Last update Mon May 19 18:28:25 2014 aurelien prieur
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
  _maxfdRead = 0;
  FD_ZERO(&this->_readfd);
}

void
Select::fdZeroWrite()
{
  _maxfdWrite = 0;
  FD_ZERO(&this->_writefd);
}

void
Select::fdSetRead(int fd)
{
  _maxfdRead = (fd > _maxfdRead) ? fd : _maxfdRead;
  FD_SET(fd, &this->_readfd);
}

void
Select::fdSetWrite(int fd)
{
  _maxfdWrite = (fd > _maxfdWrite) ? fd : _maxfdWrite;
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
  return (select((_maxfdRead > _maxfdWrite) ? _maxfdRead + 1 : _maxfdWrite + 1,
		 &this->_readfd, &this->_writefd, NULL, timeout));
}
