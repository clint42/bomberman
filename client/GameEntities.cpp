//
// GameEntities.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 18:00:17 2014 aurelien prieur
// Last update Tue Jun 10 20:38:51 2014 aurelien prieur
//

#include <iostream>
#include "GameEntities.hpp"

GameEntities::GameEntities(): _isDouble(false), _isStarted(false),
			      _player(NULL), _player2(NULL),
			      _playerScore(0), _player2Score(0),
			      _timeLeft(0)
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
  //TODO: Before erase elem from map, delete entity
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

bool				GameEntities::moveEntity(std::pair<size_t, size_t> const &coord,
							 AObject::EventIn event)
{
  AObject			*entity;
  std::pair<size_t, size_t>	newCoord(coord);
  bool				ret;

  _locker.lock();
  ret = false;
  entity = getEntity(coord);
  if (entity != NULL)
    {
      entity->addMoveEvent(event);
      if (event == AObject::DOWN)
	newCoord.second += 1;
      else if (event == AObject::UP)
	newCoord.second -= 1;
      else if (event == AObject::LEFT)
	newCoord.first -= 1;
      else if (event == AObject::RIGHT)
	newCoord.first += 1;
      _entities[newCoord] = _entities[coord];
      _entities.erase(coord);
      ret = true;
    }
  _locker.unlock();
  return (ret);
}

bool		GameEntities::rotateEntity(std::pair<size_t, size_t> const &coord,
					   AObject::EventIn event)
{
  AObject	*entity;
  glm::vec3	rotVal;
  bool		ret;

  _locker.lock();
  ret = false;
  entity = getEntity(coord);
  if (entity != NULL)
    {
      rotVal.y = event * 90;
      entity->setRotation(rotVal);
      ret = true;
    }
  _locker.unlock();
  return (ret);
}

void		GameEntities::setPlayer(int id, int nPlayer)
{
  _locker.lock();
  for (std::map<std::pair<size_t, size_t>, AObject *>::iterator it = _entities.begin();
       it != _entities.end();
       ++it)
    {
      if (it->second->getId() == id)
	{
	  if (nPlayer == 0)
	    _player = it->second;
	  else
	    _player2 = it->second;
	}
    }
  _locker.unlock();
}

AObject const	*GameEntities::getPlayer(bool withoutLock, int nPlayer)
{
  AObject	*retVal;
  
  if (!withoutLock)
    _locker.lock();
  if (nPlayer == 0)
    retVal = _player;
  else
    retVal = _player2;
  if (!withoutLock)
    _locker.unlock();
  return (retVal);
}

void		GameEntities::addPoints(int points, int nPlayer)
{
  _locker.lock();
  if (nPlayer == 0)
    _playerScore += points;
  else
    _player2Score += points;
  _locker.unlock();
}

int		GameEntities::getPlayerScore(bool withoutLock, int nPlayer)
{
  int		retVal;

  if (!withoutLock)
    _locker.lock();
  if (nPlayer == 0)
    retVal = _playerScore;
  else
    retVal = _player2Score;
  if (!withoutLock)
    _locker.unlock();
  return (retVal);
}

void		GameEntities::setTimeLeft(float const &timeLeft)
{
  _locker.lock();
  _timeLeft = timeLeft;
  _locker.unlock();
}

void		GameEntities::decreaseTimeLeft(float const &val)
{
  _locker.lock();
  if (_timeLeft < val)
    _timeLeft -= val;
  else
    _timeLeft = 0;
  _locker.unlock();
}

float		GameEntities::getTimeLeft(void)
{
  float		retVal;

  _locker.lock();
  retVal = _timeLeft;
  _locker.unlock();
  return (retVal);
}


std::pair<size_t, size_t> const &GameEntities::getMapSize(void)
{
  _locker.lock();
  std::pair<size_t, size_t> const &retVal = _mapSize;
  _locker.unlock();
  return (retVal);
}

void	GameEntities::setMapSize(std::pair<size_t, size_t> const &mapSize)
{
  _locker.lock();
  _mapSize = mapSize;
  _locker.unlock();
}

bool	GameEntities::isDouble(bool withoutLock)
{
  bool	retVal;

  if (!withoutLock)
    _locker.lock();
  retVal = _isDouble;
  if (!withoutLock)
    _locker.unlock();
  return (retVal);
}

void	GameEntities::setDouble(void)
{
  _locker.lock();
  _isDouble = true;
  _locker.unlock();
}

void	GameEntities::startGame(void)
{
  _locker.lock();
  _isStarted = true;
  _locker.unlock();
}

bool	GameEntities::isStarted(bool withoutLock)
{
  bool	retVal;

  if (!withoutLock)
    _locker.lock();
  retVal = _isStarted;
  if (!withoutLock)
    _locker.unlock();
  return (retVal);
}
