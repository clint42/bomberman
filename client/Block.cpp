//
// Block.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client/menu
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu Jun  5 12:08:48 2014 aurelien prieur
// Last update Thu Jun  5 13:58:05 2014 aurelien prieur
//

#include "Block.hpp"

Block::Block()
{
}

Block::~Block()
{
}

bool	Block::initialize(std::pair<size_t, size_t> const &pos)
{
  if (_texture.load("./assets/ublock.tga") == false)
    return (false);
  _texture.bind();
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(pos.first, 0, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 0, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 0, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first, 0, pos.second + 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(pos.first, 1, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 1, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 0, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first, 0, pos.second));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 1, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 1, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 0, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 0, pos.second));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(pos.first, 1, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 1, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 0, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first, 0, pos.second + 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(pos.first, 1, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first, 1, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first, 0, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first, 0, pos.second));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(pos.first, 1, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 1, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 1, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first, 1, pos.second + 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  if (_geometry.build() == false)
    return (false);
  return (true);
}

bool	Block::update(gdl::Clock const &clock, EventsHandler const &events)
{
  return (true);
}

void	Block::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}
