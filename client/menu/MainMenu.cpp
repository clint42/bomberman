//
// MainMenu.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 14:57:38 2014 aurelien prieur
// Last update Sun Jun 15 17:27:09 2014 virol_g
//

#include <iostream>
#include <algorithm>
#include "MainMenu.hpp"
#include "MenuBackground.hpp"
#include "MenuButton.hpp"

MainMenu::MainMenu(gdl::SdlContext &sdlContext): AMenu(sdlContext), _nbPlayers(2)
{
}

MainMenu::~MainMenu()
{
  for (size_t i = 0; i < _menuElems.size(); ++i)
    delete _menuElems[i];
  delete _menuBackground;
}

bool	MainMenu::canLoad() const
{
  ReadDir	file("./save");
  std::string	name;

  if (file.initialize() == false)
    return (false);
  while ((name = file.readFileName()) != "")
    {
      if (name != "." || name != "..")
	return (true);
    }
  return (false);
}

bool	MainMenu::build()
{
  _menuBackground = new MenuBackground("./client/menu/ressources/mainMenuBg.tga");
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(30, 205),
				      std::pair<size_t, size_t>(250, 60),
				      "New game", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike", true));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(530, 205),
				      std::pair<size_t, size_t>(270, 60),
				      "Join game", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  if ((_displayLoad = this->canLoad()) == true)
    _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(530, 305),
					std::pair<size_t, size_t>(270, 60),
					"Load game", glm::vec4(0.23, 0.18, 0.52, 1.f),
					glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(60, 500), 
				      std::pair<size_t, size_t>(100, 60),
				      "No", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike", true));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(160, 500),
				      std::pair<size_t, size_t>(100, 60),
				      "Yes", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(600, 500),
				      std::pair<size_t, size_t>(250, 60),
				      "Next", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _title = new GraphicalText("Multiplayer ?", std::pair<size_t, size_t>(50, 470),
			     glm::vec4(0.51, 0.53, 0.85, 1.f), 20, "airstrike");
  _nbPlayers = (3 - !_displayLoad);
  return (true);
}

bool	   MainMenu::update()
{
  glm::ivec2	mouse;

  this->_sdlContext.updateClock(this->_clock); 
  this->_sdlContext.updateInputs(this->_input);
  if (this->_input.getKey(SDLK_ESCAPE) || this->_input.getInput(SDL_QUIT, false))
    {
      _selected = -1;
      return (false);
    }
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
	      if (_menuElems[i]->getString() == "Next")
		return (false);
	      if (i != static_cast<size_t>(_selected) && i < (3 - !_displayLoad))
		_menuElems[_selected]->hover(false);
	      if (i != static_cast<size_t>(_nbPlayers) && i >= (3 - !_displayLoad))
		_menuElems[_nbPlayers]->hover(false);
	      if (i < (3 - !_displayLoad))
		_selected = i;
	      else if (i >= (3 - !_displayLoad))
		_nbPlayers = i;
	      _menuElems[i]->hover(true);
	    }
	}
    }
  for (size_t i = 0; i < _menuElems.size(); ++i)
    _menuElems[i]->update(_clock, _input);
  return (true);
}

void    MainMenu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _menuBackground->draw(_shader, _clock);
  for (size_t i = 0; i < _menuElems.size(); ++i)
    {
      _menuElems[i]->draw(_shader, _clock);
    }
  _title->draw(_shader);
  this->_sdlContext.flush();
}

t_game		*MainMenu::getChoice() const
{
  t_game	*options;

  if (_selected == -1)
    return (NULL);
  options = new t_game;
  options->isHost = (_selected == 0);
  options->isDouble = (_nbPlayers == (3 - !_displayLoad)) ? false : true;
  options->selected = _selected;
  return (options);
}
