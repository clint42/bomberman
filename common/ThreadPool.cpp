//
// ThreadPool.cpp for  in /home/buret_j/rendu/cpp_plazza
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Wed Apr 23 18:11:48 2014 buret_j
// Last update Sun Apr 27 22:46:12 2014 buret_j
//

#include "ThreadPool.hpp"

/* [c/d]tor */

ThreadPool::ThreadPool(size_t size)
  : _size(size), _run(true) {
  this->_cond = new CondVar(&this->_mutex);

  this->addThread(size);

  // for (std::list<ThreadPool::Thread *>::iterator i = this->_threads.begin();
  //      i != this->_threads.end(); ++i) {
  //   (*i)->join();
  // }
}

ThreadPool::~ThreadPool(void) {
  size_t	i;

  for (i = this->_threads.size(); i > 0; --i) {
    delete this->_threads.front();
    this->_threads.pop_front();
  }
}

/* launching */

static void *
ThreadTrampoline(void *);

size_t
ThreadPool::addThread(size_t amount) {
  ScopedLock		l_mutex(&this->_mutex);
  ThreadPool::Thread	*t;

  for (; amount > 0; --amount) {
    t = new ThreadPool::Thread(this, &ThreadTrampoline);
    this->_threads.push_back(t);
  }
  this->_working += amount;
  return this->_threads.size();
}

void
ThreadPool::run(void) {
  ThreadPool::task_t *task;

  while (this->_run) {
    this->_working -= 1;
    this->_mutex.lock();
    if (this->_tasks.tryPop(&task) == false) {
      this->_cond->wait();
      this->_mutex.unlock();
    }
    else {
      this->_working += 1;
      if (this->_tasks.empty() == false) {
	this->_mutex.unlock();
	this->_cond->signal();
      }
      else
	this->_mutex.unlock();
      task->funct(task->arg);
      delete task;
    }

  }
}

void
ThreadPool::addTask(ThreadPool::task_t *t) {
  this->_tasks.push(t);
  this->_cond->signal();
}

void
ThreadPool::setStop(void) {
  this->_run = false;
}

void
ThreadPool::setRun(void) {
  this->_run = true;
}

/* nested class Thread */

static void *
ThreadTrampoline(void *param) {
  ((ThreadPool *)param)->run();
  return (NULL);
}

ThreadPool::Thread::Thread(ThreadPool *tp, void *(*f)(void *)) {
  pthread_create(&this->_thread, NULL, f, tp);
}

ThreadPool::Thread::~Thread(void) {
}

void
ThreadPool::Thread::join(void) {
  pthread_join(this->_thread, NULL);
}

