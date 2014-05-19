//
// UI.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 17:52:00 2014 aurelien prieur
// Last update Mon May 19 15:10:15 2014 aurelien prieur
//

#include "UI.hpp"

UI::UI(GameEntities &gameEntities): _graphicEngine(gameEntities)
{
}

UI::~UI()
{
}

bool	UI::run()
{
  _graphicEngine.initialize();

  while (_graphicEngine.update())
    {
      _graphicEngine.draw();
    }
  return (true);
}
