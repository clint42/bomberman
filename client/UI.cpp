//
// UI.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 17:52:00 2014 aurelien prieur
// Last update Sun Jun 15 09:38:06 2014 virol_g
//

#include <unistd.h>
#include "UI.hpp"

UI::UI(EventsHandler &eventsHandler,
       GameEntities &gameEntities,
       SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs):
  _graphicEngine(eventsHandler, gameEntities, createInstructs),
  _eventsHandler(eventsHandler)
{
}

UI::~UI()
{
}

bool	UI::run()
{
  if (!_graphicEngine.initialize())
    return (false);
  while (!_eventsHandler.isFinished() && _graphicEngine.update())
    {
      _graphicEngine.draw();
    }
  _graphicEngine.stop();
  if (_eventsHandler.isEndGame())
    {
      //gdl::SdlContext *sdlContext = new gdl::SdlContext;
      // ids.push_back(1);
      // ids.push_back(-1);
      // scores.push_back(100);
      // scores.push_back(20);
      // sdlContext->start(1920, 1080, "Scores", SDL_INIT_VIDEO, SDL_WINDOW_OPENGL);
      // ScoreWindow win(*sdlContext, ids, scores, 1);
      // if (!(win.initialize()) || !(win.build()))
      // 	return (NULL);
      // while (win.update())
      // 	win.draw();
      // delete sdlContext;

    }
  return (true);
}
