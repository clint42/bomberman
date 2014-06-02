//
// GameEntities.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 16:54:40 2014 aurelien prieur
// Last update Fri May 30 17:15:21 2014 aurelien prieur
//

#ifndef GAMEENTITIES_HPP_
# define GAMEENTITIES_HPP_

# include <pthread.h>
# include <map>
# include <utility>
# include "AObject.hpp"
# include "ThreadException.hpp"
# include "Mutex.hpp"

class	GameEntities
{
  std::map<std::pair<size_t, size_t>, AObject *>	_entities;
  Mutex							_locker;

public:
  GameEntities();
  ~GameEntities();
  bool		lock();
  bool		unlock();
  bool		addEntity(std::pair<std::pair<size_t, size_t>, ObjectType> const &coord);
  bool		deleteEntity(std::pair<size_t, size_t> const &coord);
  AObject	*getEntity(std::pair<size_t, size_t> const &coord);
  std::map<std::pair<size_t, size_t>, AObject *>  &getEntities();
};

#endif // !GAMEENTITIES_HPP_
