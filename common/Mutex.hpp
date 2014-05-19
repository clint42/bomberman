//
// Mutex.hh for  in /home/buret_j/rendu/cpp_plazza/tp/ex2
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon Apr 21 14:24:02 2014 buret_j
// Last update Mon May 19 17:13:11 2014 aurelien prieur
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

  bool lock(void);
  bool unlock(void);
  bool trylock(void);

  pthread_mutex_t  *getMutex(void); // const

};

#endif
