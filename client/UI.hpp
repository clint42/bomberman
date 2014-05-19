//
// UI.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 17:33:28 2014 aurelien prieur
// Last update Mon May 19 14:33:11 2014 aurelien prieur
//

#ifndef UI_HPP
# define UI_HPP

# include "GraphicEngine.hpp"

class	UI
{
  GraphicEngine	_graphicEngine;
public:
  UI(GameEntities &gamEntities);
  ~UI();
  bool	run();
};

#endif // !UI_HPP
