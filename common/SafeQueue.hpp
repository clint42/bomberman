//
// SafeQueue.hh for  in /home/buret_j/rendu/cpp_plazza/tp/ex5
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon Apr 21 20:37:45 2014 buret_j
// Last update Sat Jun  7 22:33:10 2014 buret_j
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

  inline bool	empty() const { return this->_queue.empty(); }
  inline size_t	size() const { return this->_queue.size(); }
  inline T	front() const { return _queue.front(); }
  
};

#endif
