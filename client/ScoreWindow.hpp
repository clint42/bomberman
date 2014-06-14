//
// ScoreWindow.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Fri Jun 13 17:41:08 2014 virol_g
// Last update Fri Jun 13 17:45:54 2014 virol_g
//

#ifndef		SCOREWINDOW_HPP_
# define	SCOREWINDOW_HPP_

class		ScoreWindow
{
  std::vector<IMenuElem *>	_elems;
  std::vector<int>	_ids;
  std::vector<int>	_scores;
  gdl::SdlContext	_sdlContext;
  int			_idWiner;

public:
  ScoreWindow(std::vector<int> ids, std::vector<int> scores,
	      gdl::SdlContext sdlContext, int idWiner);
  ~ScoreWindow();
};

#endif		// !SCOREWINDOW_HPP_
