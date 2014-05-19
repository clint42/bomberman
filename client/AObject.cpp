//
// AObject.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman_ex
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 11:11:27 2014 aurelien prieur
// Last update Mon May 19 14:35:17 2014 aurelien prieur
//

#include <iostream>
#include "AObject.hpp"
#include "Model.hpp"

AObject::AObject(): _pos(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{
}

AObject::~AObject()
{
}

AObject	*AObject::create(ObjectType type)
{
  if (type == PLAYER)
    {
      return (new Model);
    }
  return (NULL);
}

bool	AObject::initialize()
{
  return (true);
}

bool	AObject::update(gdl::Clock const &clock, gdl::Input &Input)
{
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

