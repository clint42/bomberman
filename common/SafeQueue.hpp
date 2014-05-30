//
// SafeQueue.hh for  in /home/buret_j/rendu/cpp_plazza/tp/ex5
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon Apr 21 20:37:45 2014 buret_j
// Last update Fri May 30 16:33:30 2014 buret_j
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
  SafeQueue(void) { }
  ~SafeQueue(void) { }

  void		push(T v) {
    ScopedLock l_mutex(&this->_mutex);
    this->_queue.push_back(v);
  }

  bool		tryPop(T* v) {
    ScopedLock l_mutex(&this->_mutex);
    if (this->_queue.empty() == false)
      {
	*v = this->_queue.front();
	this->_queue.pop_front();
	return (true);
      }
    return (false);
  }

  bool		empty(void) {
    ScopedLock l_mutex(&this->_mutex);
    return this->_queue.empty();
  } // not const of of Mutex locked

  size_t	getSize(void) {
    ScopedLock l_mutex(&this->_mutex);
    return this->_queue.size();
  } // same
};

#endif
