//
// LoadMenu.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Sun Jun 15 10:43:50 2014 virol_g
// Last update Sun Jun 15 12:23:35 2014 virol_g
//

#ifndef		LOADMENU_HPP_
# define	LOADMENU_HPP_

# include	<vector>
# include	<sstream>
# include	"AMenu.hpp"
# include	"ReadDir.hpp"
# include	"MenuInput.hpp"
# include	"MenuScroll.hpp"
# include	"MenuBackground.hpp"
# include	"../GraphicalText.hpp"

class		LoadMenu: public AMenu
{
  MenuScroll	*_files;
  MenuInput	*_portInput;
  std::vector<GraphicalText *>	_titles;
public:
  LoadMenu(gdl::SdlContext &sdlContext);
  ~LoadMenu();

  virtual bool	build();
  virtual bool	update();
  virtual void	draw();
  bool		canFinish() const;
  t_game	*getChoice() const;
};

#endif		// !LOADMENU_HPP_
