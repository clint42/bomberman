//
// ScoreWindow.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Fri Jun 13 17:46:00 2014 virol_g
// Last update Fri Jun 13 17:51:22 2014 virol_g
//

#include	"ScoreWindow.hpp"

ScoreWindow::ScoreWindow(std::vector<int> ids, std::vector<int> scores,
	    gdl::SdlContext sdlContext, int idWiner):
  _ids(ids), _scores(scores), _sdlContext(sdlContext), _idWiner(idWiner)
{
}

ScoreWindow::~ScoreWindow()
{
  for (size_t i = 0; i < _elems.size(); ++i)
    delete _elems[i];
}

bool	ScoreWindow::initialize()
{

}
