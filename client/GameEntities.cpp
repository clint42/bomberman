//
// GameEntities.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 18:00:17 2014 aurelien prieur
// Last update Mon May 19 16:08:39 2014 aurelien prieur
//

#include <iostream>
#include "GameEntities.hpp"

GameEntities::GameEntities()
{
}

GameEntities::~GameEntities()
{
}

bool		GameEntities::lock()
{
  return (_locker.lock());
}

bool		GameEntities::unlock()
{
  return (_locker.unlock());
}

bool		GameEntities::addEntity(std::pair<size_t, size_t> const &coord, ObjectType type)
{
  AObject	*entity;
  std::pair<std::map<std::pair<size_t, size_t>, AObject *>::iterator, bool>	ret;

  entity = AObject::create(type);
  ret = _entities.insert(std::pair<std::pair<size_t, size_t>, AObject *>(coord, entity));
  ret.first->second->setPos(glm::vec3(coord.first, 0, coord.second));
  return (true);
}

bool		GameEntities::deleteEntity(std::pair<size_t, size_t> const &coord)
{
  _entities.erase(coord);
  return (true);
}

AObject		*GameEntities::getEntity(std::pair<size_t, size_t> const &coord)
{
  std::map<std::pair<size_t, size_t>, AObject *>::iterator	it;

  if ((it = _entities.find(coord)) == _entities.end())
    return (NULL);
  else
    return (it->second);
}

std::map<std::pair<size_t, size_t>, AObject *> &GameEntities::getEntities()
{
  std::cout << "Get entities" << std::endl;
  return (_entities);
}
