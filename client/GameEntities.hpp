//
// GameEntities.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 16:54:40 2014 aurelien prieur
// Last update Fri May 16 18:04:03 2014 aurelien prieur
//

#ifndef GAMEENTITIES_HPP_
# define GAMEENTITIES_HPP_

# include <pthread.h>
# include <map>
# include <utility>

class	GameEntities
{
  std::map<std::pair<size_t, size_t>, AObject *>	entities;
  pthread_mutex_t					locker;

public:
  GameEntities();
  ~GameEntities();
  bool		lock();
  bool		unlock();
  bool		addEntity(std::pair<size_t, size_t> const &coord, ObjectType type);
  bool		deleteEntity(std::pair<size_t, size_t> const &coord);
  AObject	*getEntity(std::pair<size_t, size_t> const &coord);
  std::map<std::pair<size_t, size_t>, AObject *>  const &getEntities() const;
};

#endif // !GAMEENTITIES_HPP_
