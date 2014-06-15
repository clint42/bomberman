//
// MenuBackground.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client/menu
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 26 16:09:25 2014 aurelien prieur
// Last update Sun Jun 15 01:50:56 2014 virol_g
//

#include <iostream>
#include "MenuBackground.hpp"

MenuBackground::MenuBackground(const std::string &textureName, size_t width, size_t height):
  _width(width), _height(height)
{
  this->initialize(textureName);
}

MenuBackground::~MenuBackground()
{
}

bool	MenuBackground::initialize(std::string const &textureName)
{
  if (_texture.load(textureName) == false)
    {
      std::cerr << "Couldn't load background texture." << std::endl;
      return (false);
    }
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(0, 0, -1));
  _geometry.pushVertex(glm::vec3(_width, 0, -1));
  _geometry.pushVertex(glm::vec3(_width, _height, -1));
  _geometry.pushVertex(glm::vec3(0, _height, -1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.build();
  return (true);
}

bool	MenuBackground::update(gdl::Clock const &clock, gdl::Input &input)
{
  (void)clock;
  (void)input;
  return (true);
}

void	MenuBackground::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)(clock);
  _texture.bind();
  _geometry.draw(shader, glm::mat4(1), GL_QUADS);
}

void	MenuBackground::hover(bool isHover)
{
  (void)isHover;
}

std::pair<size_t, size_t>	MenuBackground::getPos() const
{
  return (std::pair<size_t, size_t>(0, 0));
}

std::pair<size_t, size_t>	MenuBackground::getSize() const
{
  return (std::pair<size_t, size_t>(0, 0));
}

std::string			MenuBackground::getString() const
{
  return ("Background");
}
