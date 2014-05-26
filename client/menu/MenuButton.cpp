//
// MenuButton.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 12:29:16 2014 aurelien prieur
// Last update Sat May 24 20:04:43 2014 aurelien prieur
//

#include <iostream>
#include "MenuButton.hpp"

MenuButton::MenuButton(std::pair<size_t, size_t> const &pos,
		       std::pair<size_t, size_t> const &size,
		       std::string const &label,
		       glm::vec4 const &color,
		       glm::vec4 const &colorHover): _pos(pos),
						     _size(size),
						     _color(color),
						     _colorHover(colorHover),
						     _label(label, std::pair<size_t, size_t>(pos.first + 5, pos.second + 5),
							    glm::vec4(1.f, 1.f, 1.f, 1.f), size.second - 10)
{
  this->initialize("test");
}

MenuButton::~MenuButton()
{
}

bool	MenuButton::initialize(std::string const &textureName)
{
  if (_texture.load("./stone3.tga") == false)
    {
      std::cerr << "Couldn't load texture." << std::endl;
      return (false);
    }
  _geometry.setColor(_color);
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second, -1));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size.second, -1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size.first, _pos.second + _size.second, -1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size.first, _pos.second, -1));
  
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.build();

  _geometryHover.setColor(_colorHover);
  _geometryHover.pushVertex(glm::vec3(_pos.first, _pos.second, -1));
  _geometryHover.pushVertex(glm::vec3(_pos.first, _pos.second + _size.second, -1));
  _geometryHover.pushVertex(glm::vec3(_pos.first + _size.first, _pos.second + _size.second, -1));
  _geometryHover.pushVertex(glm::vec3(_pos.first + _size.first, _pos.second, -1));
  
  _geometryHover.pushUv(glm::vec2(0, 0));
  _geometryHover.pushUv(glm::vec2(1, 0));
  _geometryHover.pushUv(glm::vec2(1, 1));
  _geometryHover.pushUv(glm::vec2(0, 1));
  _geometryHover.build();
  return (true);
}

bool	MenuButton::update(gdl::Clock const &clock, gdl::Input &input)
{
  return (true);
}

void	MenuButton::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)(clock);
  _texture.bind();
  if (_isHover)
    _geometryHover.draw(shader, glm::mat4(1), GL_QUADS);
  else
    _geometry.draw(shader, glm::mat4(1), GL_QUADS);
  _label.draw(shader);
}

void	MenuButton::hover(bool isHover)
{
  _isHover = isHover;
}
