//
// ThreadPool.hpp for  in /home/buret_j/rendu/cpp_plazza
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Wed Apr 23 11:05:56 2014 buret_j
// Last update Thu May  1 14:51:32 2014 buret_j
//

#ifndef THREADPOOL_HPP_
# define THREADPOOL_HPP_

# include <list>
# include <queue>
# include <pthread.h>

# include "writeStdCOut.hpp"

# include "CondVar.hpp"
# include "Mutex.hpp"
# include "SafeQueue.hpp"
# include "ScopedLock.hpp"

// # define TASK_PER_THREAD 2

template <unsigned int TASK_PER_THREAD>
class	ThreadPool {
  class	Thread {
  private:
    pthread_t	_thread;
  public:
    Thread(ThreadPool *, void *(*)(void *));
    ~Thread(void);
    void	join(void);
  }; // !Thread

public:
  struct task_t {
    void (*funct)(void *);
    void *arg;
  };

private:
  size_t	_size;
  size_t	_working;
  bool		_run;

  CondVar		*_cond;
  Mutex			_mutex;
  std::list<Thread *>	_threads;

  SafeQueue<ThreadPool::task_t *> _tasks;

public:
	ThreadPool(size_t);
	~ThreadPool(void);
  void	run(void);

  inline size_t	getTaskFreeSlots(void) { // not const coz of SafeQueue::getSize()
    return TASK_PER_THREAD * this->_threads.size() - this->_tasks.getSize(); }
  inline size_t	getTaskTakenSlots(void) { return this->_tasks.getSize(); } // same
  inline size_t	getTaskTotalTakenSlots(void) { // same
    return this->getTaskTakenSlots() + this->getThreadWorking(); }

  inline size_t	getThreadFreeSlots(void) const {return this->_threads.size() - this->_working;}
  inline size_t getThreadWorking(void) const { return this->_working; }
  inline size_t	getThreadSleeping(void) const { return this->_threads.size() - this->_working;}
  inline size_t	size(void) const { return this->_threads.size(); }

  size_t	addThread(size_t);
  void		addTask(ThreadPool::task_t *);
  void		setStop(void);
  void		setRun(void);


}; // !ThreadPool

#endif /* !THREADPOOL_HPP_ */
