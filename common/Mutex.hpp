//
// Mutex.hh for  in /home/buret_j/rendu/cpp_plazza/tp/ex2
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon Apr 21 14:24:02 2014 buret_j
// Last update Mon May 26 18:38:59 2014 buret_j
//

#ifndef MUTEX_HH_
# define MUTEX_HH_

# include <pthread.h>

class	Mutex {

private:
  pthread_mutex_t	_mutex;

public:
  Mutex(void) { pthread_mutex_init(&this->_mutex, NULL); }
  ~Mutex(void) { pthread_mutex_destroy(&this->_mutex); }

  inline bool lock(void) { return pthread_mutex_lock(&this->_mutex) != 0 ? false : true; }
  inline bool unlock(void) { return pthread_mutex_unlock(&this->_mutex) != 0 ? false : true; }
  inline bool trylock(void) { return pthread_mutex_trylock(&this->_mutex) == 0 ? true : false; }
  inline pthread_mutex_t  *getMutex(void) { return &this->_mutex; }


};

#endif
