//
// Floor.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 30 17:39:31 2014 aurelien prieur
// Last update Sat Jun 14 17:27:02 2014 aurelien prieur
//

#include <iostream>
#include "Floor.hpp"

Floor::Floor(std::pair<size_t, size_t> const &size)
{
  _size.first = static_cast<double>(size.first);
  _size.second = static_cast<double>(size.second);
}

Floor::~Floor()
{
}

bool	Floor::initialize(std::pair<size_t, size_t> const &pos)
{
  (void)(pos);
  if (_texture.load("./client/assets/floor.tga") == false)
    {
      std::cerr << "Unable to load floor texture" << std::endl;
      return (false);
    }
  _texture.bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(0, 0, 0));
  _geometry.pushVertex(glm::vec3(_size.first, 0, 0));
  _geometry.pushVertex(glm::vec3(_size.first, 0, _size.second));
  _geometry.pushVertex(glm::vec3(0, 0, _size.second));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(_size.first, 0));
  _geometry.pushUv(glm::vec2(_size.first, _size.second));
  _geometry.pushUv(glm::vec2(0, _size.second));
  if (_geometry.build() == false)
    return (false);
  return (true);
}

bool	Floor::update(gdl::Clock const &clock, EventsHandler const &events)
{
  (void)(clock);
  (void)(events);
  return (true);
}

void	Floor::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)(clock);
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

void	Floor::setSize(std::pair<size_t, size_t> const &size)
{
  _size.first = static_cast<double>(size.first);
  _size.second = static_cast<double>(size.second);
}

std::pair<double, double> const	&Floor::getSize(void) const
{
  return (_size);
}
