//
// CondVar.hpp for Plazza in /home/virol_g/tek2/cpp/cpp_plazza
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Thu Apr 24 11:53:21 2014 virol_g
// Last update Sun Jun  8 17:33:45 2014 buret_j
//

#ifndef		CONDVAR_HPP_
# define	CONDVAR_HPP_

# include	"Mutex.hpp"

class		CondVar {

  pthread_mutex_t &_mutex;
  pthread_cond_t   _cond;

public:

  CondVar(Mutex &m) : _mutex(m.getMutex()) { }
  ~CondVar() { }
  void	wait() { pthread_cond_wait(&_cond, &_mutex); }
  void	signal() { pthread_cond_signal(&_cond); }

};

#endif		/* !CONDVAR_HPP_ */
