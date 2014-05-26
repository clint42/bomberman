//
// SafeQueue.cpp for  in /home/buret_j/rendu/cpp_plazza/tp/ex5
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon Apr 21 23:49:03 2014 buret_j
// Last update Mon May 26 18:55:20 2014 buret_j
//

#include "SafeQueue.hpp"

template <class T>
void
SafeQueue<T>::push(T v) {
  ScopedLock l_mutex(&this->_mutex);
  this->_queue.push_back(v);
}

template <class T>
bool
SafeQueue<T>::tryPop(T *v) {
  ScopedLock l_mutex(&this->_mutex);
  if (this->_queue.empty() == false)
    {
      *v = this->_queue.front();
      this->_queue.pop_front();
      return (true);
    }
  return (false);
}

template <class T>
bool
SafeQueue<T>::empty(void) {
  ScopedLock l_mutex(&this->_mutex);
  return this->_queue.empty();
}

template <class T>
size_t
SafeQueue<T>::getSize(void) {
  ScopedLock l_mutex(&this->_mutex);
  return this->_queue.size();
}
