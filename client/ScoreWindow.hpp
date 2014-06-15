//
// ScoreWindow.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Fri Jun 13 17:41:08 2014 virol_g
// Last update Sun Jun 15 01:34:35 2014 virol_g
//

#ifndef		SCOREWINDOW_HPP_
# define	SCOREWINDOW_HPP_

# include	<vector>
# include	<sstream>
# include	<SdlContext.hh>
# include	"MenuBackground.hpp"
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
  bool			_replay;

  std::string	toString(const std::string &, int);

public:
  ScoreWindow(gdl::SdlContext &sdlContext, std::vector<int> ids,
	      std::vector<int> scores, int idWiner);
  ~ScoreWindow();

  virtual bool	initialize();
  virtual bool	build();
  virtual bool	update();
  virtual void	draw();
  virtual t_game	*getChoice() const;
  bool		replay() const;
};

#endif		// !SCOREWINDOW_HPP_
