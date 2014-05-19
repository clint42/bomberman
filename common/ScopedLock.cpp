//
// ScopedLock.cpp for  in /home/buret_j/rendu/cpp_plazza/tp/ex3
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon Apr 21 16:12:44 2014 buret_j
// Last update Fri Apr 25 00:38:24 2014 buret_j
//

#include "ScopedLock.hpp"

ScopedLock::ScopedLock(Mutex *m) : _mutex(m){
  this->_mutex->lock();
}

ScopedLock::~ScopedLock(void) {
  this->_mutex->unlock();
}

