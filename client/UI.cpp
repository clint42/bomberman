//
// UI.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 17:52:00 2014 aurelien prieur
// Last update Sat Jun 14 19:47:26 2014 aurelien prieur
//

#include <unistd.h>
#include "UI.hpp"

UI::UI(EventsHandler &eventsHandler,
       GameEntities &gameEntities,
       SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs):
  _graphicEngine(eventsHandler, gameEntities, createInstructs)
{
}

UI::~UI()
{
}

bool	UI::run()
{
  if (!_graphicEngine.initialize())
    return (false);
  while (_graphicEngine.update())
    {
      _graphicEngine.draw();
    }
  _graphicEngine.stop();
  return (true);
}
