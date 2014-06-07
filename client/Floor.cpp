//
// Floor.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 30 17:39:31 2014 aurelien prieur
// Last update Thu Jun  5 13:57:25 2014 aurelien prieur
//

#include <iostream>
#include "Floor.hpp"

Floor::Floor(std::pair<size_t, size_t> const &size)
{
  _size.first = static_cast<double>(size.first) * 0.5;
  _size.second = static_cast<double>(size.second) * 0.5;
}

Floor::~Floor()
{
}

bool	Floor::initialize()
{
  if (_texture.load("./assets/floor.tga") == false)
    return (false);
  _texture.bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  // _geometry.pushVertex(glm::vec3(0 - (_size.first / 2), 0, _size.second / 2));
  // _geometry.pushVertex(glm::vec3(_size.first / 2, 0, _size.second / 2));
  // _geometry.pushVertex(glm::vec3(_size.first / 2, 0, 0 - (_size.second / 2)));
  // _geometry.pushVertex(glm::vec3(0 - (_size.first / 2), 0, 0 - (_size.second / 2)));
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

bool	Floor::update()
{
  return (true);
}

void	Floor::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}
