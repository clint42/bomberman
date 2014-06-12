//
// MainMenu.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 14:54:59 2014 aurelien prieur
// Last update Thu Jun 12 14:09:53 2014 virol_g
//

#ifndef MAINMENU_HPP_
# define MAINMENU_HPP_

# include	"../GraphicalText.hpp"
# include	"AMenu.hpp"

class	MainMenu: public AMenu
{
  int	   	_nbPlayers;
  GraphicalText	*_title;

public:
  MainMenu(gdl::SdlContext &sdlContext);
  ~MainMenu();
  virtual bool	build();
  virtual bool	update();
  virtual void	draw();
  virtual t_game	*getChoice() const;
};

#endif // !MAINMENU_HPP_
