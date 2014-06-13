//
// JoinMenu.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Wed Jun 11 14:19:39 2014 virol_g
// Last update Fri Jun 13 14:18:25 2014 virol_g
//

#include	<fstream>
#include	<sstream>
#include	"JoinMenu.hpp"

JoinMenu::JoinMenu(gdl::SdlContext &sdlContext): AMenu(sdlContext)
{
}

JoinMenu::~JoinMenu()
{
  delete _menuBackground;
  delete _join;
  delete _readPort;
  delete _readIP;
  delete _titleIP;
  delete _titlePort;
}

bool	JoinMenu::build()
{
  _menuBackground = new MenuBackground("./client/menu/ressources/backgroundSubMenu.tga");
  _join = new MenuButton(std::pair<size_t, size_t>(500, 500),
			 std::pair<size_t, size_t>(150, 60),
			 "Join", glm::vec4(0.23, 0.18, 0.52, 1.f),
			 glm::vec4(0.23, 0.18, 0.52, 1.f), "airstrike");
  _readIP = new MenuInput(std::pair<size_t, size_t>(400, 300),
			 std::pair<size_t, size_t>(380, 60),
			  glm::vec4(0.23, 0.18, 0.52, 1.f), glm::vec4(0.51, 0.53, 0.85, 1.f));
  _readPort = new MenuInput(std::pair<size_t, size_t>(400, 150),
			 std::pair<size_t, size_t>(380, 60),
			  glm::vec4(0.23, 0.18, 0.52, 1.f), glm::vec4(0.51, 0.53, 0.85, 1.f));
  _titleIP = new GraphicalText("Enter IP adress",
			     std::pair<size_t, size_t>(400, 280),
			     glm::vec4(0.23, 0.18, 0.52, 1.f), 20, "airstrike");
  _titlePort = new GraphicalText("Server port",
			     std::pair<size_t, size_t>(400, 130),
			     glm::vec4(0.23, 0.18, 0.52, 1.f), 20, "airstrike");
  return (true);
}

bool	JoinMenu::update()
{
  glm::ivec2	mouse;

  this->_sdlContext.updateClock(this->_clock);
  this->_sdlContext.updateInputs(this->_input);
  if (this->_input.getKey(SDLK_ESCAPE) || this->_input.getInput(SDL_QUIT, false))
    {
      _selected = -1;
      return (false);
    }
  if (this->_input.getKey(SDL_BUTTON_LEFT))
    {
      mouse = this->_input.getMousePosition();
      if (static_cast<size_t>(mouse.x) > _readIP->getPos().first &&
	  static_cast<size_t>(mouse.x) < _readIP->getPos().first + _readIP->getSize().first &&
	  static_cast<size_t>(mouse.y) > _readIP->getPos().second &&
	  static_cast<size_t>(mouse.y) < _readIP->getPos().second + _readIP->getSize().second)
	_readIP->hover(true);
      else
	_readIP->hover(false);
      if (static_cast<size_t>(mouse.x) > _readPort->getPos().first &&
	  static_cast<size_t>(mouse.x) < _readPort->getPos().first + _readPort->getSize().first &&
	  static_cast<size_t>(mouse.y) > _readPort->getPos().second &&
	  static_cast<size_t>(mouse.y) < _readPort->getPos().second + _readPort->getSize().second)
	_readPort->hover(true);
      else
	_readPort->hover(false);
      if (static_cast<size_t>(mouse.x) > _join->getPos().first &&
	  static_cast<size_t>(mouse.x) < _join->getPos().first + _join->getSize().first &&
	  static_cast<size_t>(mouse.y) > _join->getPos().second &&
	  static_cast<size_t>(mouse.y) < _join->getPos().second + _join->getSize().second &&
	  _readIP->getString() != "" && _readPort->getString() != "")
	return (false);
    }
  _readIP->update(_clock, _input);
  _readPort->update(_clock, _input);
  return (true);
}

void	JoinMenu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _menuBackground->draw(_shader, _clock);
  _readIP->draw(_shader, _clock);
  _readPort->draw(_shader, _clock);
  _titleIP->draw(_shader);
  _titlePort->draw(_shader);
  _join->draw(_shader, _clock);
  _sdlContext.flush();
}

t_game	*JoinMenu::getChoice() const
{
  std::stringstream	ss;
  t_game	*choice = new t_game;

  if (_selected == -1)
    return (NULL);
  choice->ipAddr = _readIP->getString();
  ss << _readPort->getString();
  ss >> choice->serverPort;
  return (choice);
}
