//
// MenuInput.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Wed Jun  4 18:35:29 2014 virol_g
// Last update Fri Jun 13 01:43:33 2014 virol_g
//

#ifndef		MENUINPUT_HPP_
# define	MENUINPUT_HPP_

# include	<iostream>
# include	"../GraphicalText.hpp"
# include	"IMenuElem.hpp"

class		MenuInput : public IMenuElem
{
  glm::vec4			_color;
  glm::vec4			_colorHover;
  gdl::Texture			_texture;
  gdl::Geometry			_geometry;
  gdl::Geometry			_geometryHover;
  GraphicalText			_output;
  std::pair<size_t, size_t>	_pos;
  std::pair<size_t, size_t>	_size;
  std::map<int, std::pair<char, bool> >	_keys;
  bool				_hover;
public:
  MenuInput(std::pair<size_t, size_t> const &pos,
	    std::pair<size_t, size_t> const &size,
	    glm::vec4 const &color, const glm::vec4 &colorHover);
  ~MenuInput();
  virtual bool	initialize(std::string const &textureName);
  virtual bool	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual void	hover(bool isHover);
  virtual std::string	getString() const;

  std::pair<size_t, size_t>	getPos() const;
  std::pair<size_t, size_t>	getSize() const;
  bool				isHover() const;
};

#endif		// MENUINPUT_HPP_
