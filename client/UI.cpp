//
// UI.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 17:52:00 2014 aurelien prieur
// Last update Fri May 30 15:14:39 2014 aurelien prieur
//

#include "UI.hpp"

UI::UI(EventsHandler &eventsHandler,
       GameEntities &gameEntities,
       SafeQueue<std::pair<std::pair<size_t, size_t>, ObjectType> > &createInstructs):
  _graphicEngine(eventsHandler, gameEntities, createInstructs)
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
