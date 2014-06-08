//
// CondSafeQueue.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Sun Jun  8 16:38:49 2014 buret_j
// Last update Sun Jun  8 17:24:32 2014 buret_j
//

#ifndef CONDSAFEQUEUE_HPP_
# define CONDSAFEQUEUE_HPP_

# include <queue>
# include "Mutex.hpp"
# include "CondVar.hpp"

template <class T>
class	CondSafeQueue {

  Mutex		_mutex;
  CondVar	_cond;
  std::queue<T>	_queue;

  CondSafeQueue(CondSafeQueue const &c) { (void)c; }
  CondSafeQueue &operator=(CondSafeQueue const &c) { (void)c; return *this; }

public:

  CondSafeQueue() : _mutex(), _cond(_mutex) { }
  ~CondSafeQueue() { }

  void	push(T v) {
    _mutex.lock();
    _queue.push(v);
    _mutex.unlock();
    _cond.signal();
  }

  bool	tryPop(T *v) {
    _mutex.lock();
    if (this->_queue.empty() == false)
      {
	*v = this->_queue.front();
	this->_queue.pop();
	_mutex.unlock();
	return (true);
      }
    _mutex.unlock();
    return (false);
  }

  void	wait() { _cond.wait();  }
  void  signal() { _cond.signal(); }
  bool	empty() { return _queue.empty(); }

};

#endif
