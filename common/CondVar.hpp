//
// CondVar.hpp for Plazza in /home/virol_g/tek2/cpp/cpp_plazza
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Thu Apr 24 11:53:21 2014 virol_g
// Last update Fri Apr 25 00:49:23 2014 buret_j
//

#ifndef		CONDVAR_HPP_
# define	CONDVAR_HPP_

# include	"Mutex.hpp"

class		CondVar
{
  pthread_mutex_t *_mutex;
  pthread_cond_t  _cond;

public:
	CondVar(Mutex *);
	~CondVar();
  void	wait(void);
  void	signal(void);
};

#endif		/* !CONDVAR_HPP_ */
