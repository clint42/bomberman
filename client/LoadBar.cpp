//
// LoadBar.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat Jun 14 22:19:54 2014 aurelien prieur
// Last update Sun Jun 15 01:49:21 2014 aurelien prieur
//

#include <iostream>
#include "LoadBar.hpp"

LoadBar::LoadBar(gdl::SdlContext &sdlContext, gdl::AShader &shader): _sdlContext(sdlContext),
								     _shader(shader),
								     _loaderGauge(NULL)
{
  
}

LoadBar::~LoadBar()
{
}

bool	LoadBar::initialize(std::pair<float, float> const &pos,
			    std::pair<float, float> const &size)
{
  float	sizeSides;

  _size = size;
  _pos = pos;
  if (!_borderTexture.load("./client/assets/loaderBorderCenter.tga") ||
      !_borderLeftTexture.load("./client/assets/loaderBorderLeft.tga") ||
      !_borderRightTexture.load("./client/assets/loaderBorderRight.tga") ||
      !_loaderTexture.load("./client/assets/loaderInside.tga"))
    {
      std::cerr << "Couldn't load loader textures" << std::endl;
      return (false);
    }
  sizeSides = 32;
  _borderLeft.setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
  _borderLeft.pushVertex(glm::vec3(pos.first, pos.second, 0.f));
  _borderLeft.pushVertex(glm::vec3(pos.first + sizeSides, pos.second, 0.f));
  _borderLeft.pushVertex(glm::vec3(pos.first + sizeSides, pos.second + size.second, 0.f));
  _borderLeft.pushVertex(glm::vec3(pos.first, pos.second + size.second, 0.f));
  _borderLeft.pushUv(glm::vec2(1, 1));
  _borderLeft.pushUv(glm::vec2(0, 1));
  _borderLeft.pushUv(glm::vec2(0, 0));
  _borderLeft.pushUv(glm::vec2(1, 0));
  _borderLeft.build();

  _border.setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
  _border.pushVertex(glm::vec3(pos.first + sizeSides, pos.second, 0.f));
  _border.pushVertex(glm::vec3(pos.first + size.first, pos.second, 0.f));
  _border.pushVertex(glm::vec3(pos.first + size.first, pos.second + size.second, 0.f));
  _border.pushVertex(glm::vec3(pos.first + sizeSides, pos.second + size.second, 0.f));
  _border.pushUv(glm::vec2(1, 1));
  _border.pushUv(glm::vec2(0, 1));
  _border.pushUv(glm::vec2(0, 0));
  _border.pushUv(glm::vec2(1, 0));
  _border.build();

  _borderRight.setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
  _borderRight.pushVertex(glm::vec3(pos.first + size.first, pos.second, 0.f));
  _borderRight.pushVertex(glm::vec3(pos.first + size.first + sizeSides, pos.second, 0.f));
  _borderRight.pushVertex(glm::vec3(pos.first + size.first + sizeSides, pos.second + size.second, 0.f));
  _borderRight.pushVertex(glm::vec3(pos.first + size.first, pos.second + size.second, 0.f));
  _borderRight.pushUv(glm::vec2(1, 1));
  _borderRight.pushUv(glm::vec2(0, 1));
  _borderRight.pushUv(glm::vec2(0, 0));
  _borderRight.pushUv(glm::vec2(1, 0));
  _borderRight.build();
  return (true);
}

bool	LoadBar::update(int valueLoaded)
{
  float	size;

  if (_loaderGauge != NULL)
    delete _loaderGauge;
  _loaderGauge = new gdl::Geometry;
  size = (valueLoaded * _size.first) / 100.f;
  _loaderGauge->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
  _loaderGauge->pushVertex(glm::vec3(_pos.first, _pos.second, 0.5));
  _loaderGauge->pushVertex(glm::vec3(_pos.first + size, _pos.second, 0.5));
  _loaderGauge->pushVertex(glm::vec3(_pos.first + size, _pos.second + _size.second, 0.5));
  _loaderGauge->pushVertex(glm::vec3(_pos.first, _pos.second + _size.second, 0.5));
  _loaderGauge->pushUv(glm::vec2(1, 1));
  _loaderGauge->pushUv(glm::vec2(0, 1));
  _loaderGauge->pushUv(glm::vec2(0, 0));
  _loaderGauge->pushUv(glm::vec2(1, 0));
  _loaderGauge->build();
  this->draw();
  return (true);
}

void	LoadBar::draw(void)
{
  std::cout << "Draw loader" << std::endl;
  _shader.bind();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  _borderTexture.bind();
  _borderLeft.draw(_shader, glm::mat4(1), GL_QUADS);
  _borderTexture.bind();
  _border.draw(_shader, glm::mat4(1), GL_QUADS);
  _borderTexture.bind();
  _borderRight.draw(_shader, glm::mat4(1), GL_QUADS);
  _loaderTexture.bind();
  _loaderGauge->draw(_shader, glm::mat4(1), GL_QUADS);
  glDisable(GL_BLEND);
  _sdlContext.flush();
}
