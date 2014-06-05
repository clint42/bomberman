//
// GameEntities.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 18:00:17 2014 aurelien prieur
// Last update Thu Jun  5 12:03:13 2014 aurelien prieur
//

#include <iostream>
#include "Model.hpp"
#include "GameEntities.hpp"

GameEntities::GameEntities(): _player(NULL)
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

bool		GameEntities::addEntity(std::pair<std::pair<size_t, size_t>, int> const &desc)
{
  AObject	*entity;
  std::pair<std::map<std::pair<size_t, size_t>, AObject *>::iterator, bool>	ret;

  _locker.lock();
  if ((entity = AObject::create(desc.second)) != NULL)
    {
      if (entity->initialize(desc.first) == false)
	{
	  _locker.unlock();
	  return (false);
	}
      _entities.insert(std::pair<std::pair<size_t, size_t>, AObject *>(desc.first, entity));
    }
  else
    {
      _locker.unlock();
      return (false);
    }
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

bool		GameEntities::moveEntity(std::pair<size_t, size_t> const &coord,
					 AObject::EventIn event)
{
  AObject	*entity;

  _locker.lock();
  entity = getEntity(coord);
  entity->addMoveEvent(event);
  _locker.unlock();
  return (true);
}

bool		GameEntities::rotateEntity(std::pair<size_t, size_t> const &coord,
					   AObject::EventIn event)
{
  AObject	*entity;
  glm::vec3	rotVal;

  _locker.lock();
  entity = getEntity(coord);
  rotVal.y = event * 90;
  entity->setRotation(rotVal);
  _locker.unlock();
  return (true);
}

void		GameEntities::setPlayer(int id)
{
  _locker.lock();
  for (std::map<std::pair<size_t, size_t>, AObject *>::iterator it = _entities.begin();
       it != _entities.end();
       ++it)
    {
      std::cout << "it->second->getId()" << it->second->getId() << std::endl;
      if (it->second->getId() == id)
	_player = it->second;
    }
  _locker.unlock();
}

AObject const	*GameEntities::getPlayer(void) const
{
  return (_player);
}
