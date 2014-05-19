/*
** Select.hpp for Select in /home/lafitt_g/Tek2/c++/bomberman/common
** 
** Made by lafitt_g
** Login   <lafitt_g@lafittg>
** 
** Started on  Mon May 19 14:59:44 2014 lafitt_g
// Last update Mon May 19 18:27:41 2014 aurelien prieur
*/

#ifndef SELECT_HPP_
# define SELECT_HPP_

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

class		Select
{
public:
  Select();
  ~Select();

  void		fdZeroRead();
  void		fdSetRead(int);
  int		fdIssetRead(int);
  void		fdZeroWrite();
  void		fdSetWrite(int);
  int		fdIssetWrite(int);
  int		fdSelect(struct timeval *timeout);

private:
  fd_set	_readfd;
  fd_set	_writefd;
  int		_maxfdRead;
  int		_maxfdWrite;
};

#endif /* !SELECT_HPP_ */
