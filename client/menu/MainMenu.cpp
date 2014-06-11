//
// MainMenu.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 14:57:38 2014 aurelien prieur
// Last update Wed Jun 11 13:50:24 2014 aurelien prieur
//

#include <iostream>
#include <algorithm>
#include "MainMenu.hpp"
#include "MenuBackground.hpp"
#include "MenuButton.hpp"

MainMenu::MainMenu(gdl::SdlContext &sdlContext): AMenu(sdlContext)
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
  return (true);
}

t_game		*MainMenu::getChoice() const
{
  t_game	*options;

  options = new t_game;
  options->isHost = (_selected == 0);
  return (options);
}
