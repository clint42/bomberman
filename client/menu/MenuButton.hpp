//
// MenuButton.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 12:24:33 2014 aurelien prieur
// Last update Thu May 29 14:46:02 2014 aurelien prieur
//

#ifndef MENUBUTTON_HPP_
# define MENUBUTTON_HPP_

# include <string>
# include "IMenuElem.hpp"
# include "GraphicalText.hpp"

class	MenuButton: public IMenuElem
{
  glm::vec4                     _color;
  glm::vec4                     _colorHover;
  gdl::Texture                  _texture;
  gdl::Geometry                 _geometry;
  gdl::Geometry			_geometryHover;
  std::pair<size_t, size_t>     _pos;
  std::pair<size_t, size_t>	_size;
  bool                          _isHover;
  GraphicalText			_label;

public:
  MenuButton(std::pair<size_t, size_t> const &pos,
	     std::pair<size_t, size_t> const &size,
	     std::string const &_label,
	     glm::vec4 const &color, glm::vec4 const &colorHover,
	     std::string const &font = "impact");
  ~MenuButton();
  virtual bool	initialize(std::string const &textureName);
  virtual bool	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual void	hover(bool isHover);
};

#endif // !MENUBUTTON_HPP_
