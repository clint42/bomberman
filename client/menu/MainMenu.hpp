//
// MainMenu.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 14:54:59 2014 aurelien prieur
// Last update Mon May 26 13:16:21 2014 aurelien prieur
//

#ifndef MAINMENU_HPP_
# define MAINMENU_HPP_

# include "AMenu.hpp"

class	MainMenu: public AMenu
{
public:
  MainMenu();
  ~MainMenu();
  virtual bool	build();
  virtual int	getChoice() const;
};

#endif // !MAINMENU_HPP_
