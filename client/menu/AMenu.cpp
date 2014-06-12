//
// AMenu.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 11:12:45 2014 aurelien prieur
// Last update Thu Jun 12 14:08:03 2014 virol_g
//

#include <unistd.h>
#include <iostream>
#include "AMenu.hpp"

AMenu::AMenu(gdl::SdlContext &sdlContext): _sdlContext(sdlContext), _selected(0)
{
  _key[0] = false;
  _key[1] = false;
}

AMenu::~AMenu()
{
}

bool    AMenu::initialize()
{
  glm::mat4     projection;

  // if (this->_sdlStarted == false)
  //   this->_sdlContext.start(800, 600, "Menu", SDL_INIT_VIDEO, SDL_WINDOW_OPENGL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!_shader.load("./client/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./client/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    {
      std::cerr << "Shader loading error" << std::endl;
      return (false);
    }
  projection = glm::ortho(0.f, 800.f, 600.f, 0.f, -1.f, 1.f);
  _shader.bind();
  _shader.setUniform("projection", projection);
  _shader.setUniform("view", glm::mat4(1));
  return (true);
}

gdl::SdlContext	AMenu::getContext() const
{
  return (this->_sdlContext);
}
