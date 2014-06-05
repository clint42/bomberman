//
// GameEntities.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 16:54:40 2014 aurelien prieur
// Last update Wed Jun  4 18:23:29 2014 aurelien prieur
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
  AObject						*_player;
  std::map<std::pair<size_t, size_t>, AObject *>	_entities;
  Mutex							_locker;

public:
  GameEntities();
  ~GameEntities();
  bool		lock();
  bool		unlock();
  bool		addEntity(std::pair<std::pair<size_t, size_t>, int> const &coord);
  bool		deleteEntity(std::pair<size_t, size_t> const &coord);
  AObject	*getEntity(std::pair<size_t, size_t> const &coord);
  std::map<std::pair<size_t, size_t>, AObject *>  &getEntities();
  bool		moveEntity(std::pair<size_t, size_t> const &coord,
			   AObject::EventIn event);
  bool		rotateEntity(std::pair<size_t, size_t> const &coord,
			     AObject::EventIn event);
  void		setPlayer(int id);
  AObject const	*getPlayer(void) const;
};

#endif // !GAMEENTITIES_HPP_
