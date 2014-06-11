//
// MenuScroll.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Sat Jun  7 17:58:22 2014 virol_g
// Last update Wed Jun 11 17:45:43 2014 virol_g
//

#include	<iostream>
#include	"MenuScroll.hpp"

MenuScroll::MenuScroll(const std::pair<size_t, size_t> &posPrev,
		       const std::pair<size_t, size_t> &posNext,
		       const std::pair<size_t, size_t> &size, const glm::vec4 &color,
		       const glm::vec4 &colorHover) :
  _scroll(posNext, size, "->", color, colorHover),
  _scrollPrev(posPrev, size, "<-", color, colorHover),
  _display(0), _clickPrev(false), _clickNext(false)
{
  this->initialize("./client/menu/ressources/gradationGreyTex.tga");
}

MenuScroll::~MenuScroll()
{
}

bool		MenuScroll::initialize(__attribute__((unused))const std::string &textureName)
{
  return (true);
}

bool		MenuScroll::update(const gdl::Clock &clock, gdl::Input &input)
{
  glm::ivec2	mouse;

  if (_list.size() > 0)
    {
      _scroll.update(clock, input);
      _scrollPrev.update(clock, input);
      if (input.getKey(SDL_BUTTON_LEFT))
	{
	  mouse = input.getMousePosition();
	  if ((static_cast<size_t>(mouse.x) > _scroll.getPos().first &&
	       static_cast<size_t>(mouse.x) < _scroll.getPos().first + _scroll.getSize().first) &&
	      (static_cast<size_t>(mouse.y) > _scroll.getPos().second &&
	       static_cast<size_t>(mouse.y) < _scroll.getPos().second + _scroll.getSize().second) &&
	      _clickNext == false)
	    {
	      (_display == _list.size() - 1) ? (_display = 0) : _display += 1;
	      _clickNext = true;
	    }
	  else if ((static_cast<size_t>(mouse.x) > _scrollPrev.getPos().first &&
		    static_cast<size_t>(mouse.x) < _scrollPrev.getPos().first + _scrollPrev.getSize().first) &&
		   (static_cast<size_t>(mouse.y) > _scrollPrev.getPos().second &&
		    static_cast<size_t>(mouse.y) < _scrollPrev.getPos().second + _scrollPrev.getSize().second) &&
		   _clickPrev == false)
	    {
	      (_display == 0) ? (_display = _list.size() - 1) : _display -= 1;
	      _clickPrev = true;
	    }
	  else
	    {
	      _clickPrev = false;
	      _clickNext = false;
	    }
	}
    }
  return (true);
}

void		MenuScroll::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  if (_list.size() > 0)
    {
      _scroll.draw(shader, clock);
      _scrollPrev.draw(shader, clock);
      _list[_display]->draw(shader, clock);
    }
}

void		MenuScroll::hover(bool isHover)
{
  _isHover = isHover;
  _scroll.hover(isHover);
}

void		MenuScroll::addElem(MenuButton *newElem)
{
  _list.push_back(newElem);
}

std::pair<size_t, size_t>	MenuScroll::getPos() const
{
  return (_scroll.getPos());
}

std::pair<size_t, size_t>	MenuScroll::getSize() const
{
  return (_scroll.getSize());
}

std::string	MenuScroll::getChoice() const
{
  return (_list[_display]->getString());
}
