//
// CreateMenu.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Tue Jun 10 15:51:47 2014 virol_g
// Last update Fri Jun 13 13:42:56 2014 virol_g
//

#ifndef		CREATEMENU_HPP_
# define	CREATEMENU_HPP_

# include	"AMenu.hpp"
# include	"MenuBackground.hpp"
# include	"MenuInput.hpp"
# include	"MenuScroll.hpp"
# include	"MenuButton.hpp"
# include	"../GraphicalText.hpp"

# define	P_FONT_SIZE 20
class		CreateMenu : public AMenu
{
  MenuScroll	*_selectMap;
  std::vector<MenuInput *>	_inputs;
  std::vector<GraphicalText *>	_titles;

  bool		canFinish() const;
public:
  CreateMenu(gdl::SdlContext &sdlContext);
  ~CreateMenu();

  virtual bool	build();
  virtual bool	update();
  virtual void	draw();
  t_game	*getChoice() const;
};

#endif		// !CREATEMENU_HPP_
