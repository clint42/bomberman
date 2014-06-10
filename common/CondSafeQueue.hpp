//
// CondSafeQueue.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Sun Jun  8 16:38:49 2014 buret_j
// Last update Tue Jun 10 12:34:05 2014 buret_j
//

#ifndef CONDSAFEQUEUE_HPP_
# define CONDSAFEQUEUE_HPP_

# include <list>
# include "Mutex.hpp"
# include "CondVar.hpp"

template <class T>
class	CondSafeQueue {

  Mutex		_mutex;
  CondVar	_cond;
  std::list<T>	_queue;

  CondSafeQueue(CondSafeQueue const &c) { (void)c; }
  CondSafeQueue &operator=(CondSafeQueue const &c) { (void)c; return *this; }

public:

  CondSafeQueue() : _mutex(), _cond(_mutex) { }
  ~CondSafeQueue() { }

  void	push(T v) {
    _mutex.lock();
    _queue.push_back(v);
    _mutex.unlock();
    _cond.signal();
  }
  void	push_front(T v) {
    _mutex.lock();
    _queue.push_front(v);
    _mutex.unlock();
  }

  bool	tryPop(T *v) {
    _mutex.lock();
    if (this->_queue.empty() == false)
      {
	*v = this->_queue.front();
	this->_queue.pop_front();
	_mutex.unlock();
	return (true);
      }
    _mutex.unlock();
    return (false);
  }

  void	wait() { _cond.wait(); }
  void  signal() { _cond.signal(); }
  bool	empty() const { return _queue.empty(); }

};

#endif
