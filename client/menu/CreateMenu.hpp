//
// CreateMenu.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Tue Jun 10 15:51:47 2014 virol_g
// Last update Wed Jun 11 10:56:33 2014 aurelien prieur
//

#ifndef		CREATEMENU_HPP_
# define	CREATEMENU_HPP_

# include	"AMenu.hpp"
# include	"MenuBackground.hpp"
# include	"MenuInput.hpp"
# include	"MenuScroll.hpp"
# include	"MenuButton.hpp"
# include	"GraphicalText.hpp"

# define	P_FONT_SIZE 20
class		CreateMenu : public AMenu
{
  MenuInput	*_nbPlayers;
  MenuInput	*_nbBots;
  MenuScroll	*_selectMap;
  std::vector<GraphicalText *>	_titles;

public:
  CreateMenu(gdl::SdlContext &sdlContext);
  ~CreateMenu();

  virtual bool	build();
  virtual bool	update();
  virtual void	draw();
  t_game	*getChoice() const;
};

#endif		// !CREATEMENU_HPP_
