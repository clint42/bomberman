//
// SafeQueue.hh for  in /home/buret_j/rendu/cpp_plazza/tp/ex5
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon Apr 21 20:37:45 2014 buret_j
// Last update Fri Apr 25 15:46:32 2014 buret_j
//

#ifndef SAFEQUEUE_HPP_
# define SAFEQUEUE_HPP_

# include <list>
# include "Mutex.hpp"
# include "ScopedLock.hpp"

template <class T>
class	SafeQueue {

private:
  Mutex		_mutex;
  std::list<T>	_queue;

public:
  SafeQueue(void);
  ~SafeQueue(void);
  void		push(T);
  bool		tryPop(T*);
  bool		empty(void); // not const of of Mutex locked
  size_t	getSize(void); // same
};

#endif
