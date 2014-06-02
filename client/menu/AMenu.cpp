//
// AMenu.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 11:12:45 2014 aurelien prieur
// Last update Mon Jun  2 14:04:27 2014 virol_g
//

#include <unistd.h>
#include <iostream>
#include "AMenu.hpp"

AMenu::AMenu(): _selected(0)
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

  this->_sdlContext.start(800, 600, "Menu", SDL_INIT_VIDEO, SDL_WINDOW_OPENGL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!_shader.load("../shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("../shaders/basic.vp", GL_VERTEX_SHADER)
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

bool    AMenu::update()
{
  this->_sdlContext.updateClock(this->_clock); 
  this->_sdlContext.updateInputs(this->_input);
  if (this->_input.getKey(SDLK_ESCAPE) || this->_input.getInput(SDL_QUIT, false))
    {
      _selected = -1;
      return (false);
    }
  if (this->_input.getKey(SDLK_RETURN))
    return (false);
  if (_selected >= 0)
    _menuElems[_selected]->hover(false);
  if (_input.getKey(SDLK_LEFT))
    _key[1] = true;
  else if (_input.getKey(SDLK_RIGHT))
    _key[0] = true;
  else if (_key[1])
    {
      _key[1] = false;
      _selected = (_selected + 1 < static_cast<int>(_menuElems.size())) ? _selected + 1 : 0;
    }  
  else if (_key[0])
    {
      _key[0] = false;
      _selected = (_selected - 1 >= 0) ? _selected - 1 : _menuElems.size() - 1;
    }  
  if (_selected >= 0)
    _menuElems[_selected]->hover(true);
  for (size_t i = 0; i < _menuElems.size(); ++i)
    _menuElems[i]->update(_clock, _input);
  return (true);
}

void    AMenu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  for (size_t i = 0; i < _menuElems.size(); ++i)
    _menuElems[i]->draw(_shader, _clock);
  this->_sdlContext.flush();
}

void	AMenu::timer()
{
  if (_clock.getElapsed() < (1.f / 60.f))
    {
      usleep((1.f / 60.f - _clock.getElapsed()) * 1000000);
    }
}
