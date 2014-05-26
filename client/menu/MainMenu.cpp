//
// MainMenu.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 14:57:38 2014 aurelien prieur
// Last update Mon May 26 13:15:35 2014 aurelien prieur
//

#include <algorithm>
#include "MainMenu.hpp"
#include "MenuButton.hpp"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
  for (size_t i = 0; i < _menuElems.size(); ++i)
    delete _menuElems[i];
}

bool	MainMenu::build()
{
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(250, 100),
				      std::pair<size_t, size_t>(300, 50),
				     "New game...",
				       glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4(0.93, 0.90, 0.32, 1.f)));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(250, 170),
				      std::pair<size_t, size_t>(300, 50),
				      "Join game...",
				      glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4(0.93, 0.90, 0.32, 1.f)));
  return (true);
}

int	MainMenu::getChoice() const
{
  return (_selected);
}
