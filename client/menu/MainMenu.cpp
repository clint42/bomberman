//
// MainMenu.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 14:57:38 2014 aurelien prieur
// Last update Wed Jun 11 17:28:44 2014 virol_g
//

#include <iostream>
#include <algorithm>
#include "MainMenu.hpp"
#include "MenuBackground.hpp"
#include "MenuButton.hpp"

MainMenu::MainMenu(gdl::SdlContext &sdlContext): AMenu(sdlContext), _nbPlayers(2)
{
  // this->_sdlStarted = false;
}

MainMenu::~MainMenu()
{
  for (size_t i = 0; i < _menuElems.size(); ++i)
    delete _menuElems[i];
  delete _menuBackground;
}

bool	MainMenu::build()
{
  _menuBackground = new MenuBackground("./client/menu/ressources/mainMenuBg.tga");
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(30, 205),
				      std::pair<size_t, size_t>(250, 60),
				     "New game",
				      glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4(0.93, 0.90, 0.32, 1.f),
				      "airstrike"));

  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(530, 205),
				      std::pair<size_t, size_t>(250, 60),
				      "Join game",
				      glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4(0.93, 0.90, 0.32, 1.f),
				      "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(30, 500), 
				      std::pair<size_t, size_t>(250, 60),
				      "1 Player", glm::vec4(0.f, 0.f, 1.f, 1.f),
				      glm::vec4(0.93, 0.9, 0.32, 1.f), "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(530, 500),
				      std::pair<size_t, size_t>(250, 60),
				      "2 Players", glm::vec4(0.f, 0.f, 1.f, 1.f),
				      glm::vec4(0.93, 0.9, 0.32, 1.f), "airstrike"));
  return (true);
}

bool    MainMenu::update()
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
	      if (i != static_cast<size_t>(_selected) && i < 2)
		_menuElems[_selected]->hover(false);
	      if (i != static_cast<size_t>(_nbPlayers) && i >= 2)
		_menuElems[_nbPlayers]->hover(false);
	      if (i < 2)
		_selected = i;
	      else if (i >= 2)
		_nbPlayers = i;
	      _menuElems[i]->hover(true);
	    }
	}
    }
  for (size_t i = 0; i < _menuElems.size(); ++i)
    _menuElems[i]->update(_clock, _input);
  return (true);
}

t_game		*MainMenu::getChoice() const
{
  t_game	*options;

  options = new t_game;
  options->isHost = (_selected == 0);
  options->isDouble = (_nbPlayers == 2) ? false : true;
  return (options);
}
