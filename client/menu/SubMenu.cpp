//
// SubMenu.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Tue Jun  3 14:49:50 2014 virol_g
// Last update Tue Jun 10 14:18:26 2014 virol_g
//

#include	"MenuScroll.hpp"
#include	"MenuInput.hpp"
#include	"SubMenu.hpp"
#include	"MenuButton.hpp"
#include	"MenuBackground.hpp"

SubMenu::SubMenu(gdl::SdlContext sdlContext)
{
  this->_sdlContext = sdlContext;
  this->_sdlStarted = true;
}

SubMenu::~SubMenu()
{
  delete _menuBackground;
  for (size_t i = 0; i < _menuElems.size(); ++i)
    delete _menuElems[i];
}

bool	SubMenu::build()
{
  MenuScroll	*scroll = new MenuScroll(std::pair<size_t, size_t>(80, 205),
					 std::pair<size_t, size_t>(250, 205),
					 std::pair<size_t, size_t>(80, 60),
					 glm::vec4(0.f, 0.f, 1.f, 1.f),
					 glm::vec4(0.93, 0.9, 0.32, 1.f));
  
  _menuBackground = new MenuBackground();
  scroll->addElem(new MenuButton(std::pair<size_t, size_t>(80, 145),
  				      std::pair<size_t, size_t>(250, 60),
  				      "Test",
  				      glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4(0.93, 0.9, 0.32, 1.f),
  				      "airstrike"));
  scroll->addElem(new MenuButton(std::pair<size_t, size_t>(70, 145),
  				      std::pair<size_t, size_t>(250, 60),
  				      "Test2",
  				      glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4(0.93, 0.9, 0.32, 1.f),
  				      "airstrike"));
  scroll->addElem(new MenuButton(std::pair<size_t, size_t>(70, 145),
  				      std::pair<size_t, size_t>(250, 60),
  				      "Test3",
  				      glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4(0.93, 0.9, 0.32, 1.f),
  				      "airstrike"));
  scroll->addElem(new MenuButton(std::pair<size_t, size_t>(70, 145),
  				      std::pair<size_t, size_t>(250, 60),
  				      "Test4",
  				      glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4(0.93, 0.9, 0.32, 1.f),
  				      "airstrike"));
  _menuElems.push_back(new MenuInput(std::pair<size_t, size_t>(530, 205),
				      std::pair<size_t, size_t>(250, 60),
				     glm::vec4(0.f, 0.f, 1.f, 1.f)));
  _menuElems.push_back(scroll);
  return (true);
}

int	SubMenu::getChoice() const
{
  return (_selected);
}
