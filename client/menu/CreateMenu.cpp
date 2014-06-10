//
// CreateMenu.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Tue Jun 10 15:52:26 2014 virol_g
// Last update Tue Jun 10 20:02:40 2014 virol_g
//

#include	<fstream>
#include	"CreateMenu.hpp"

CreateMenu::CreateMenu(gdl::SdlContext sdlContext)
{
  _sdlContext = sdlContext;
  _sdlStarted = true;
}

CreateMenu::~CreateMenu()
{
  delete _menuBackground;
  delete _nbPlayers;
  delete _selectMap;
  delete _nbBots;
  for (size_t i = 0; i < _menuElems.size(); ++i)
    delete _menuElems[i];
}

bool	CreateMenu::build()
{
  std::ifstream	file("maps");
  std::string	name;

  _selectMap = new MenuScroll(std::pair<size_t, size_t>(400, 360),
  			      std::pair<size_t, size_t>(650, 360),
  			      std::pair<size_t, size_t>(80, 60),
  			      glm::vec4(0.f, 0.f, 1.f, 1.f),
  			      glm::vec4(0.93, 0.9, 0.32, 1.f));
  if (file)
    {
      while (getline(file, name))
	{
	  _selectMap->addElem(new MenuButton(std::pair<size_t, size_t>(400, 300),
					    std::pair<size_t, size_t>(330, 60),
					    name, glm::vec4(0.f, 0.f, 1.f, 1.f),
					    glm::vec4(0.93, 0.9, 0.32, 1.f)));
	}
    }
  _menuBackground = new MenuBackground();
  _nbPlayers = new MenuInput(std::pair<size_t, size_t>(400, 80),
			     std::pair<size_t, size_t>(250, 60),
			     glm::vec4(0.f, 0.f, 1.f, 1.f));
  _nbBots = new MenuInput(std::pair<size_t, size_t>(400, 120),
			     std::pair<size_t, size_t>(250, 60),
			     glm::vec4(0.f, 0.f, 1.f, 1.f));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(400, 200),
				      std::pair<size_t, size_t>(85, 60),
				      "Short", glm::vec4(0.f, 0.f, 1.f, 1.f),
				      glm::vec4(0.93, 0.9, 0.32, 1.f), "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(400, 200),
				      std::pair<size_t, size_t>(85, 60),
				      "Medium", glm::vec4(0.f, 0.f, 1.f, 1.f),
				      glm::vec4(0.93, 0.9, 0.32, 1.f), "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(400, 200),
				      std::pair<size_t, size_t>(85, 60),
				      "Long", glm::vec4(0.f, 0.f, 1.f, 1.f),
				      glm::vec4(0.93, 0.9, 0.32, 1.f), "airstrike"));
  return (true);
}

bool	CreateMenu::update()
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
      for (size_t i = 0; i < _menuElems.size(); ++i)
	{
	  if (mouse.x > _menuElems[i]->getPos().first && mouse.x < _menuElems[i]->getPos().first + _menuElems[i]->getSize().first &&
	      mouse.y > _menuElems[i]->getPos().second && mouse.y < _menuElems[i]->getPos().second + _menuElems[i]->getSize().second)
	    {
	      if (i != _selected)
		_menuElems[_selected]->hover(false);
	      _selected = i;
	      _menuElems[i]->hover(true);
	      // return (false);
	    }
	}
    }
  for (size_t i = 0; i < _menuElems.size(); ++i)
    _menuElems[i]->update(_clock, _input);
  _selectMap->update(_clock, _input);
  _nbPlayers->update(_clock, _input);
  return (true);
}

void	CreateMenu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _menuBackground->draw(_shader, _clock);
  _nbPlayers->draw(_shader, _clock);
  _selectMap->draw(_shader, _clock);
  for (size_t i = 0; i < _menuElems.size(); ++i)
    _menuElems[i]->draw(_shader, _clock);
  _sdlContext.flush();
}
