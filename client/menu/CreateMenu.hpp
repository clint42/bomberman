//
// CreateMenu.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Tue Jun 10 15:51:47 2014 virol_g
// Last update Tue Jun 10 19:59:04 2014 virol_g
//

#ifndef		CREATEMENU_HPP_
# define	CREATEMENU_HPP_

# include	"AMenu.hpp"
# include	"MenuBackground.hpp"
# include	"MenuInput.hpp"
# include	"MenuScroll.hpp"
# include	"MenuButton.hpp"

typedef struct	s_game
{
  std::string	mapName;
  size_t	nbPlayers;
  size_t	timeGame;
}		t_game;

class		CreateMenu : public AMenu
{
  MenuInput	*_nbPlayers;
  MenuInput	*_nbBots;
  MenuScroll	*_selectMap;
  // std::vector<MenuButton *>	_timeGame;

public:
  CreateMenu(gdl::SdlContext sdlContext);
  ~CreateMenu();

  virtual bool	build();
  virtual bool	update();
  virtual void	draw();
  t_game	*getChoice() const;
};

#endif		// !CREATEMENU_HPP_
