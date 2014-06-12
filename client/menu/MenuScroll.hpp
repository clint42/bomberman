//
// MenuScroll.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Sat Jun  7 17:54:57 2014 virol_g
// Last update Thu Jun 12 13:44:13 2014 virol_g
//

#ifndef		MENUSCROLL_HPP_
# define	MENUSCROLL_HPP_

# include	"IMenuElem.hpp"
# include	"MenuButton.hpp"

class		MenuScroll : public IMenuElem
{
  std::vector<MenuButton *>	_list;
  MenuButton		_scroll;
  MenuButton		_scrollPrev;
  std::string		_choice;
  size_t		_display;
  bool			_isHover;
  glm::vec4		_color;
  glm::vec4		_colorHover;
  gdl::Texture		_texture;
  gdl::Geometry		_geometry;
  gdl::Geometry		_geometryHover;
  bool			_clickPrev;
  bool			_clickNext;

public:
  MenuScroll(const std::pair<size_t, size_t> &posPrev,
	     const std::pair<size_t, size_t> &posNext,
	     const std::pair<size_t, size_t> &size, const glm::vec4 &color,
	     const glm::vec4 &colorHover);
  ~MenuScroll();

  virtual bool		initialize(const std::string &textureName);
  virtual bool		update(const gdl::Clock &clock, gdl::Input &input);
  virtual void		draw(gdl::AShader &shader, const gdl::Clock &clock);
  virtual void		hover(bool isHover);

  void			addElem(MenuButton *newButton);

  virtual std::pair<size_t, size_t>	getPos() const;
  virtual std::pair<size_t, size_t>	getSize() const;

  virtual std::string	getString() const;
};

# endif		// !MENUSCROLL_HPP_
