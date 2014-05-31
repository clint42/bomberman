//
// CondVar.cpp for  in /home/buret_j/rendu/cpp_plazza
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Thu Apr 24 23:31:15 2014 buret_j
// Last update Fri Apr 25 00:48:38 2014 buret_j
//

#include "CondVar.hpp"

CondVar::CondVar(Mutex *m) {
  this->_mutex = m->getMutex();
}

CondVar::~CondVar(void) {
}

void
CondVar::wait(void) {
  pthread_cond_wait(&this->_cond, this->_mutex);
}

void
CondVar::signal(void) {
  pthread_cond_signal(&this->_cond);
}
