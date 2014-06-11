//
// JoinMenu.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Wed Jun 11 14:18:25 2014 virol_g
// Last update Wed Jun 11 14:53:44 2014 virol_g
//

#ifndef		JOINMENU_HPP_
# define	JOINMENU_HPP_

# include	"AMenu.hpp"
# include	"MenuInput.hpp"
# include	"MenuBackground.hpp"

class		JoinMenu : public AMenu
{
  MenuInput	*_readIP;
  GraphicalText	*_title;
public:
  JoinMenu(gdl::SdlContext &);
  ~JoinMenu();

  virtual bool	build();
  virtual void	draw();
  virtual bool	update();

  t_game	*getChoice() const;
};

#endif		// !JOINMENU_HPP_
