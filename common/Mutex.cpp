//
// Mutex.cpp for  in /home/buret_j/rendu/cpp_plazza
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Wed Apr 23 19:35:42 2014 buret_j
// Last update Sun Jun  8 16:49:05 2014 buret_j
//

#include "Mutex.hpp"

Mutex::Mutex(void) {
  pthread_mutex_init(&this->_mutex, NULL);
}

Mutex::~Mutex(void) {
  pthread_mutex_destroy(&this->_mutex);
}

bool
Mutex::lock(void) {
  if (pthread_mutex_lock(&this->_mutex) != 0)
    return (false);
  return (true);
}

bool
Mutex::unlock(void) {
  if (pthread_mutex_unlock(&this->_mutex) != 0)
    return (false);
  return (true);
}

bool
Mutex::trylock(void) {
  return (pthread_mutex_trylock(&this->_mutex) == 0 ? true : false);
}

pthread_mutex_t &
Mutex::getMutex(void) {
  return _mutex;
}
