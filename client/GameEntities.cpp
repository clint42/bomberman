//
// GameEntities.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 18:00:17 2014 aurelien prieur
// Last update Fri May 30 15:23:54 2014 aurelien prieur
//

#include <iostream>
#include "Model.hpp"
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

bool		GameEntities::addEntity(std::pair<std::pair<size_t, size_t>, ObjectType> const &desc)
{
  AObject	*entity;
  std::pair<std::map<std::pair<size_t, size_t>, AObject *>::iterator, bool>	ret;

  //entity = AObject::create(type);
  _locker.lock();
  // ret = _entities.insert(std::pair<std::pair<size_t, size_t>, AObject *>(coord, entity));
  // //ret.first->second->setPos(glm::vec3(coord.first, 0, coord.second));
  entity = new Model();
  if (entity->initialize() == false)
    return (false);
  std::cout << "ENTITY: " << entity << std::endl;
  _entities.insert(std::pair<std::pair<size_t, size_t>, AObject *>(desc.first, entity));
  //entity->scale(glm::vec3(0.02, 0.02, 0.02));
  _locker.unlock();
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
  return (_entities);
}
