//
// SubMenu.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Tue Jun  3 14:44:19 2014 virol_g
// Last update Tue Jun 10 15:59:12 2014 virol_g
//

#ifndef		SUBMENU_HPP_
# define	SUBMENU_HPP_

# include	"AMenu.hpp"

class		SubMenu : public AMenu
{
public:
  SubMenu(gdl::SdlContext);
  ~SubMenu();
  virtual bool	build();
  int		getChoice() const;
};

#endif		// !SUBMENU_HPP_
