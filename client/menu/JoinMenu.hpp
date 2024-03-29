//
// JoinMenu.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Wed Jun 11 14:18:25 2014 virol_g
// Last update Fri Jun 13 14:09:23 2014 virol_g
//

#ifndef		JOINMENU_HPP_
# define	JOINMENU_HPP_

# include	"AMenu.hpp"
# include	"MenuInput.hpp"
# include	"MenuButton.hpp"
# include	"MenuBackground.hpp"

class		JoinMenu : public AMenu
{
  MenuButton	*_join;
  MenuInput	*_readIP;
  MenuInput	*_readPort;
  
  GraphicalText	*_titleIP;
  GraphicalText	*_titlePort;
public:
  JoinMenu(gdl::SdlContext &);
  ~JoinMenu();

  virtual bool	build();
  virtual void	draw();
  virtual bool	update();

  t_game	*getChoice() const;
};

#endif		// !JOINMENU_HPP_
