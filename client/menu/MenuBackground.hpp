//
// MenuBackground.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client/menu
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 26 16:04:21 2014 aurelien prieur
// Last update Mon May 26 16:21:56 2014 aurelien prieur
//

#ifndef MENUBACKGROUND_HPP_
# define MENUBACKGROUND_HPP_

# include "IMenuElem.hpp"

class	MenuBackground: public IMenuElem
{
  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
public:
  MenuBackground();
  virtual ~MenuBackground();
  virtual bool	initialize(std::string const &textureName);
  virtual bool	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual void	hover(bool isHover);
};

#endif // !MENUBACKGROUND_HPP_
