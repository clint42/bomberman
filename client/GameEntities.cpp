//
// GameEntities.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 18:00:17 2014 aurelien prieur
// Last update Fri May 16 18:05:08 2014 aurelien prieur
//

#include "GameEntities.hpp"

GameEntities::GameEntities()
{
}

GameEntities::~GameEntities()
{
}

bool		GameEntities::lock()
{

}

bool		GameEntities::unlock()
{

}

bool		GameEntities::addEntity(std::pair<size_t, size_t> const &coord, ObjectType type)
{
  
}

bool		GameEntities::deleteEntity(std::pair<size_t, size_t>)
{

}

AObject		*getEntity(std::pair<size_t, size_t> const &coord)
{
  
}

std::map<std::pair<size_t, size_t>, AObject *> const &getEntities() const
{
  return (_entities);
}
