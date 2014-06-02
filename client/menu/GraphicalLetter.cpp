//
// GraphicalLetter.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 13:23:05 2014 aurelien prieur
// Last update Mon Jun  2 14:33:53 2014 virol_g
//

#include <iostream>
#include "GraphicalLetter.hpp"

GraphicalLetter::GraphicalLetter(char letter, std::pair<size_t, size_t> const &pos,
				 glm::vec4 const &color,
				 float const &fontSize,
				 gdl::Texture const &texture): _abcTex(texture), 
							       _pos(pos),
							       _fontSize(fontSize),
							       _color(color)
{
  float	origX;
  float	origY;
  float	sizeLetter;

  origX = letter % 16;
  origY = 15 - letter / 16;
  sizeLetter = static_cast<float>(_abcTex.getWidth()) / 16.f;
  sizeLetter /= static_cast<float>(_abcTex.getWidth());
  origX /= 16.f;
  origY /= 16.f;
  _geometry.setColor(_color);
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second, 0));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _fontSize, 0));
  _geometry.pushVertex(glm::vec3(_pos.first + _fontSize, _pos.second + _fontSize, 0));
  _geometry.pushVertex(glm::vec3(_pos.first + _fontSize, _pos.second, 0));
  _geometry.pushUv(glm::vec2(origX, origY + sizeLetter));
  _geometry.pushUv(glm::vec2(origX, origY));
  _geometry.pushUv(glm::vec2((origX + sizeLetter), origY));
  _geometry.pushUv(glm::vec2((origX + sizeLetter), origY + sizeLetter));
  _geometry.build();
}

GraphicalLetter::~GraphicalLetter()
{
}

void	GraphicalLetter::draw(gdl::AShader &shader)
{
  _geometry.draw(shader, glm::mat4(1), GL_QUADS);
}

void	GraphicalLetter::updateColor(glm::vec4 const &color)
{
  _color = color;
  _geometry.setColor(color);
}
