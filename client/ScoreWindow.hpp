//
// ScoreWindow.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Fri Jun 13 17:41:08 2014 virol_g
// Last update Sat Jun 14 17:46:22 2014 virol_g
//

#ifndef		SCOREWINDOW_HPP_
# define	SCOREWINDOW_HPP_

# include	<vector>
# include	<sstream>
# include	"menu/AMenu.hpp"
# include	"menu/IMenuElem.hpp"
# include	"MenuButton.hpp"

class		ScoreWindow: public AMenu
{
  std::vector<IMenuElem *>	_elems;
  std::vector<GraphicalText *>	_text;
  std::vector<int>	_ids;
  std::vector<int>	_scores;
  int			_idWiner;
  size_t		_nbPlayers;

  std::string	toString(const std::string &, int);

public:
  ScoreWindow(std::vector<int> ids, std::vector<int> scores,
	      gdl::SdlContext sdlContext, int idWiner);
  ~ScoreWindow();

  bool		build();
};

#endif		// !SCOREWINDOW_HPP_
