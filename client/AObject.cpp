//
// AObject.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman_ex
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 11:11:27 2014 aurelien prieur
// Last update Sat Jun 14 12:35:26 2014 aurelien prieur
//

#include <iostream>
#include "AObject.hpp"
#include "Player.hpp"
#include "Block.hpp"
#include "Bomb.hpp"
#include "Fire.hpp"
#include "Bonus.hpp"

AObject::AObject(): _id(0), _pos(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1), _target(0, 0, 0),
		    _direction(DOWN), _moving(false), _moveVectors(4)
{
}

AObject::AObject(int id): _id(id), _pos(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1), _target(0, 0, 0),
		    _direction(DOWN), _moving(false), _moveVectors(4)
{
  
  _moveVectors[DOWN] = glm::vec3(0, 0, 1);
  _moveVectors[RIGHT] = glm::vec3(1, 0, 0);
  _moveVectors[UP] = glm::vec3(0, 0, -1);
  _moveVectors[LEFT] = glm::vec3(-1, 0, 0);
}

AObject::~AObject()
{
}

AObject	*AObject::create(int objectType)
{

  if (objectType == BLOCK || objectType == BOX)
    {
      return (new Block(static_cast<ObjectType>(objectType)));
    }
  else if (objectType >= BONUSSPEED && objectType <= BONUSBOMB)
    {
      return (new Bonus(static_cast<ObjectType>(objectType)));
    }
  else if (objectType == BOMB)
    {
      return (new Bomb);
    }
  else if (objectType == FIRE)
    {
      return (new Fire);
    }
  else if (objectType > PLAYER)
    {
      return (new Player(objectType - PLAYER));
    }
  return (NULL);
}

bool	AObject::initialize(std::pair<size_t, size_t> const &pos)
{
  (void)(pos);
  return (true);
}

bool	AObject::update(gdl::Clock const &clock, EventsHandler const &events)
{
  (void)(events);
  (void)(clock);
  return (true);
}

void	AObject::translate(glm::vec3 const &v)
{
  _pos += v;
}

void	AObject::rotate(glm::vec3 const &axis, float angle)
{
  _rotation += axis * angle;
  _rotation.x = (_rotation.x >= 360) ? _rotation.x - 360 : _rotation.x;
  _rotation.y = (_rotation.y >= 360) ? _rotation.y - 360 : _rotation.y;
  _rotation.z = (_rotation.z >= 360) ? _rotation.z - 360 : _rotation.z;
  std::cout << _rotation.x << ";" << _rotation.y << ";" << _rotation.z << std::endl;
}

void	AObject::setRotation(glm::vec3 const &rotation)
{
  _rotation = rotation;
}

glm::vec3 const	&AObject::getRotation() const
{
  return (_rotation);
}

void	AObject::scale(glm::vec3 const &scale)
{
  _scale *= scale;
}

void	AObject::setPos(glm::vec3 const &pos)
{
  _pos = pos;
}

void	AObject::setScale(glm::vec3 const &scale)
{
  _scale = scale;
}

glm::mat4	AObject::getTransformation()
{
  glm::mat4	transform(1);

  transform = glm::translate(transform, _pos);
  transform = glm::scale(transform, _scale);
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));  
  return (transform);
}

void		AObject::addMoveEvent(EventIn event)
{
  _moveEvents.push_back(event);
}

bool		AObject::equalVec3(glm::vec3 const &vec1, glm::vec3 const &vec2)
{
  if (vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z)
    return (true);
  return (false);
}

bool		AObject::superiorVec3(glm::vec3 const &vec1, glm::vec3 const &vec2, EventIn direction)
{
  if ((direction == AObject::RIGHT || direction == AObject::DOWN) &&
      (vec1.x > vec2.x || vec1.y > vec2.y || vec1.z > vec2.z))
    return (true);
  else if ((direction == AObject::LEFT || direction == AObject::UP) &&
	   (vec1.x < vec2.x || vec1.y < vec2.y || vec1.z < vec2.z))
    return (true);
  return (false);
}

glm::vec3 const	&AObject::getPos(void) const
{
  return (_pos);
}

int	AObject::getId(void) const
{
  return (_id);
}
