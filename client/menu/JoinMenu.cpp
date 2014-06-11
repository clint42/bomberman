//
// JoinMenu.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Wed Jun 11 14:19:39 2014 virol_g
// Last update Wed Jun 11 14:57:45 2014 virol_g
//

#include	"JoinMenu.hpp"

JoinMenu::JoinMenu(gdl::SdlContext &sdlContext): AMenu(sdlContext)
{
  // this->_sdlContext = sdlContext;
  // this->_sdlStarted = true;
}

JoinMenu::~JoinMenu()
{
}

bool	JoinMenu::build()
{
  _menuBackground = new MenuBackground("./client/menu/ressources/backgroundSubMenu.tga");
  _readIP = new MenuInput(std::pair<size_t, size_t>(400, 300),
			 std::pair<size_t, size_t>(380, 60),
			 glm::vec4(1.f, 1.f, 1.f, 1.f));
  _title = new GraphicalText("Enter IP adress",
			     std::pair<size_t, size_t>(400, 280),
			     glm::vec4(0.f, 0.f, 1.f, 1.f), 20, "airstrike");
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
  if (this->_input.getKey(SDLK_RETURN))
    return (false);
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
    }
  _readIP->update(_clock, _input);
  return (true);
}

void	JoinMenu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _menuBackground->draw(_shader, _clock);
  _readIP->draw(_shader, _clock);
  _title->draw(_shader);
  _sdlContext.flush();
}

t_game	*JoinMenu::getChoice() const
{
  t_game	*choice = new t_game;

  choice->ipAddr = _readIP->getInput();
  return (choice);
}
