//
// Thread.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Sun Jun  8 14:33:57 2014 buret_j
// Last update Sun Jun  8 16:53:43 2014 buret_j
//

#ifndef THREAD_HPP_
# define THREAD_HPP_

# include <pthread.h>

class	Thread {

  pthread_t	_thread;

  Thread(Thread const &t) { (void)t; }
  Thread &operator=(Thread const &t) { (void)t; return *this; }

public:

  Thread(void* (*f)(void *), void *p) { pthread_create(&_thread, NULL, f, p); }
  ~Thread() { pthread_join(this->_thread, NULL); }

};

#endif /* !THREAD_HPP_ */
