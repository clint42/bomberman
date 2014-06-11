//
// AMenu.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 11:12:45 2014 aurelien prieur
// Last update Wed Jun 11 10:50:01 2014 aurelien prieur
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
  if (!_shader.load("./shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./shaders/basic.vp", GL_VERTEX_SHADER)
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
  glm::ivec2	mouse;

  this->_sdlContext.updateClock(this->_clock); 
  this->_sdlContext.updateInputs(this->_input);
  if (this->_input.getKey(SDLK_ESCAPE) || this->_input.getInput(SDL_QUIT, false))
    {
      _selected = -1;
      return (false);
    }
  if (this->_input.getKey(SDLK_RETURN))
    return (false);
  if (this->_input.getKey(SDL_BUTTON_LEFT))
    {
      mouse = this->_input.getMousePosition();
      for (size_t i = 0; i < _menuElems.size(); ++i)
	{
	  if (static_cast<size_t>(mouse.x) > _menuElems[i]->getPos().first &&
	      static_cast<size_t>(mouse.x) < _menuElems[i]->getPos().first + _menuElems[i]->getSize().first &&
	      static_cast<size_t>(mouse.y) > _menuElems[i]->getPos().second &&
	      static_cast<size_t>(mouse.y) < _menuElems[i]->getPos().second + _menuElems[i]->getSize().second)
	    {
	      if (i != static_cast<size_t>(_selected))
		_menuElems[_selected]->hover(false);
	      _selected = i;
	      _menuElems[i]->hover(true);
	      // return (false);
	    }
	}
    }
  for (size_t i = 0; i < _menuElems.size(); ++i)
    _menuElems[i]->update(_clock, _input);
  return (true);
}

void    AMenu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _menuBackground->draw(_shader, _clock);
  for (size_t i = 0; i < _menuElems.size(); ++i)
    {
      _menuElems[i]->draw(_shader, _clock);
    }
  this->_sdlContext.flush();
}

void	AMenu::timer()
{
  if (_clock.getElapsed() < (1.f / 60.f))
    {
      usleep((1.f / 60.f - _clock.getElapsed()) * 1000000);
    }
}

gdl::SdlContext	AMenu::getContext() const
{
  return (this->_sdlContext);
}
