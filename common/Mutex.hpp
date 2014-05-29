//
// Mutex.hh for  in /home/buret_j/rendu/cpp_plazza/tp/ex2
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon Apr 21 14:24:02 2014 buret_j
// Last update Thu May 29 17:56:58 2014 aurelien prieur
//

#ifndef MUTEX_HH_
# define MUTEX_HH_

# include <pthread.h>

class	Mutex {

private:
  pthread_mutex_t	_mutex;

public:
  Mutex(void);
  ~Mutex(void);

  inline bool lock(void);
  inline bool unlock(void);
  inline bool trylock(void);
  inline pthread_mutex_t  *getMutex(void);
};

#endif
