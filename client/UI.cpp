//
// UI.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 17:52:00 2014 aurelien prieur
// Last update Sun Jun 15 20:15:55 2014 aurelien prieur
//

#include <unistd.h>
#include "UI.hpp"
#include "ScoreWindow.hpp"

UI::UI(EventsHandler &eventsHandler,
       GameEntities &gameEntities,
       SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs):
  _graphicEngine(eventsHandler, gameEntities, createInstructs),
  _eventsHandler(eventsHandler),
  _gameEntities(gameEntities)
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
      gdl::SdlContext *sdlContext = new gdl::SdlContext;
      std::vector<int>	ids(2);
      std::vector<int>	scores(2);

      ids.push_back(0);
      scores.push_back(_gameEntities.getPlayerScore(false, 0));
      if (_gameEntities.isDouble())
	{
	  ids.push_back(1);
	  scores.push_back(_gameEntities.getPlayerScore(false, 1));
	}
      else
	{
	  ids.push_back(-1);
	  scores.push_back(-1);
	}
      sdlContext->start(1920, 1080, "Scores", SDL_INIT_VIDEO, SDL_WINDOW_OPENGL);
      ScoreWindow win(*sdlContext, ids, scores, 1);
      if (!(win.initialize()) || !(win.build()))
      	return (false);
      while (win.update())
      	win.draw();
      sdlContext->stop();
      delete sdlContext;
      return (win.replay());
    }
  return (false);
}
