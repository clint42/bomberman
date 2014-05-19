//
// ScopedLock.hh for  in /home/buret_j/rendu/cpp_plazza/tp/ex3
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon Apr 21 16:04:50 2014 buret_j
// Last update Thu Apr 24 23:37:47 2014 buret_j
//

#ifndef SCOPEDLOCK_HH_
# define SCOPEDLOCK_HH_

# include "Mutex.hpp"

class	ScopedLock {

private:
  Mutex	*_mutex;

  ScopedLock(ScopedLock const &);
  ScopedLock &operator=(ScopedLock const &);

public:
  ScopedLock(Mutex *);
  ~ScopedLock(void);

};

#endif
