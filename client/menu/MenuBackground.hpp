//
// MenuBackground.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client/menu
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 26 16:04:21 2014 aurelien prieur
// Last update Sun Jun 15 01:49:32 2014 virol_g
//

#ifndef MENUBACKGROUND_HPP_
# define MENUBACKGROUND_HPP_

# include "IMenuElem.hpp"

class	MenuBackground: public IMenuElem
{
  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
  size_t	_width;
  size_t	_height;
public:
  MenuBackground(const std::string &, size_t width = 800, size_t height = 600);
  virtual ~MenuBackground();
  virtual bool	initialize(std::string const &textureName);
  virtual bool	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual void	hover(bool isHover);
  virtual std::pair<size_t, size_t>	getPos() const;
  virtual std::pair<size_t, size_t>	getSize() const;
  virtual std::string			getString() const;
};

#endif // !MENUBACKGROUND_HPP_
