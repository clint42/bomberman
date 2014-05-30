
//
// MainMenu.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 14:57:38 2014 aurelien prieur
// Last update Thu May 29 14:56:12 2014 aurelien prieur
//

#include <algorithm>
#include "MainMenu.hpp"
#include "MenuBackground.hpp"
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
  _menuElems.push_back(new MenuBackground());
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

int	MainMenu::getChoice() const
{
  return (_selected);
}
