//
// MapMenu.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Fri Jun 13 20:23:41 2014 virol_g
// Last update Sat Jun 14 14:12:28 2014 virol_g
//

#ifndef		MAPMENU_HPP_
# define	MAPMENU_HPP

# include	<sstream>
# include	"MenuButton.hpp"
# include	"MenuInput.hpp"
# include	"MenuBackground.hpp"
# include	"../GraphicalText.hpp"
# include	"AMenu.hpp"

class		MapMenu: public AMenu
{
  std::vector<GraphicalText *>	_titles;
  bool		canFinish() const;
public:
  MapMenu(gdl::SdlContext &sdlContext);
  ~MapMenu();

  virtual bool	build();
  virtual bool	update();
  virtual void	draw();
  t_game	*getChoice() const;
  int		getInfo(const std::string &) const;
};

#endif		// !MAPMENU_HPP_
