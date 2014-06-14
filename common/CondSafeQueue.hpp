//
// CondSafeQueue.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Sun Jun  8 16:38:49 2014 buret_j
// Last update Sat Jun 14 15:31:02 2014 buret_j
//

#ifndef CONDSAFEQUEUE_HPP_
# define CONDSAFEQUEUE_HPP_

# include <list>
# include "Mutex.hpp"
# include "CondVar.hpp"

template <class T>
class	CondSafeQueue {

  Mutex		_mutexThread;
  Mutex		_mutexQueue;
  CondVar	_cond;
  std::list<T>	_queue;

  CondSafeQueue(CondSafeQueue const &c) { (void)c; }
  CondSafeQueue &operator=(CondSafeQueue const &c) { (void)c; return *this; }

public:

  CondSafeQueue() : _mutexThread(), _mutexQueue(), _cond(_mutexThread) { }
  ~CondSafeQueue() { }

  void	push(T v) {
    std::cout << "CondSafeQueue::push() => avant lock" << std::endl;
    _mutexQueue.lock();
    std::cout << "CondSafeQueue::push() => c'est lock" << std::endl;
    _queue.push_back(v);
    std::cout << "CondSafeQueue::push() => avant delock" << std::endl;
    _mutexQueue.unlock();
    std::cout << "CondSafeQueue::push() => c'est delock" << std::endl;
    // _cond.signal();
    std::cout << "CondSafeQueue::push() => j'ai signal ma condvar" << std::endl;
  }
  void	push_front(T v) {
    _mutexQueue.lock();
    _queue.push_front(v);
    _mutexQueue.unlock();
  }

  bool	tryPop(T *v) {
    _mutexQueue.lock();
    if (this->_queue.empty() == false)
      {
	*v = this->_queue.front();
	this->_queue.pop_front();
	_mutexQueue.unlock();
	return (true);
      }
    _mutexQueue.unlock();
    return (false);
  }

  void	wait() { _cond.wait(); }
  void  signal() { _cond.signal(); }
  bool	empty() const { return _queue.empty(); }

};

#endif
