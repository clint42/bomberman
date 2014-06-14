//
// MapMenu.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Fri Jun 13 20:24:40 2014 virol_g
// Last update Sat Jun 14 18:08:38 2014 virol_g
//

#include	"MapMenu.hpp"

MapMenu::MapMenu(gdl::SdlContext &sdlContext): AMenu(sdlContext)
{
}

MapMenu::~MapMenu()
{
  for (size_t i = 0; i < _menuElems.size(); ++i)
    delete _menuElems[i];
}

bool		MapMenu::build()
{
  _menuBackground = new MenuBackground("./client/menu/ressources/backgroundSubMenu.tga");
  _menuElems.push_back(new MenuInput(std::pair<size_t, size_t>(400, 100),
				     std::pair<size_t, size_t>(380, 60),
				     glm::vec4(0.23, 0.18, 0.52, 1.f),
				     glm::vec4(0.51, 0.53, 0.85, 1.f)));
  _menuElems.push_back(new MenuInput(std::pair<size_t, size_t>(400, 200),
				     std::pair<size_t, size_t>(380, 60),
				     glm::vec4(0.23, 0.18, 0.52, 1.f),
				     glm::vec4(0.51, 0.53, 0.85, 1.f)));
  _menuElems.push_back(new MenuInput(std::pair<size_t, size_t>(400, 300),
				     std::pair<size_t, size_t>(380, 60),
				     glm::vec4(0.23, 0.18, 0.52, 1.f),
				     glm::vec4(0.51, 0.53, 0.85, 1.f)));
  _menuElems.push_back(new MenuInput(std::pair<size_t, size_t>(400, 400),
				     std::pair<size_t, size_t>(380, 60),
				     glm::vec4(0.23, 0.18, 0.52, 1.f),
				     glm::vec4(0.51, 0.53, 0.85, 1.f)));

  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(600, 550),
				      std::pair<size_t, size_t>(200, 60),
				      "Create", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f)));
  _titles.push_back(new GraphicalText("Map width", std::pair<size_t, size_t>(400, 80),
				     glm::vec4(0.23, 0.18, 0.52, 1.f), 20, "airstrike"));
  _titles.push_back(new GraphicalText("Map height", std::pair<size_t, size_t>(400, 180),
				     glm::vec4(0.23, 0.18, 0.52, 1.f), 20, "airstrike"));
  _titles.push_back(new GraphicalText("Players on the map", std::pair<size_t, size_t>(400, 280),
				     glm::vec4(0.23, 0.18, 0.52, 1.f), 20, "airstrike"));
  _titles.push_back(new GraphicalText("Map name", std::pair<size_t, size_t>(400, 380),
				     glm::vec4(0.23, 0.18, 0.52, 1.f), 20, "airstrike"));
  return (true);
}

bool		MapMenu::canFinish() const
{
  for (size_t i = 0; i < _menuElems.size(); ++i)
    {
      if (_menuElems[i]->getString() == "")
	return (false);
    }
  return (true);
}

bool		MapMenu::update()
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
      for (size_t i = 0; i < _menuElems.size(); ++i)
	{
	  if (static_cast<size_t>(mouse.x) > _menuElems[i]->getPos().first &&
	      static_cast<size_t>(mouse.x) < _menuElems[i]->getPos().first + _menuElems[i]->getSize().first &&
	      static_cast<size_t>(mouse.y) > _menuElems[i]->getPos().second &&
	      static_cast<size_t>(mouse.y) < _menuElems[i]->getPos().second + _menuElems[i]->getSize().second)
	    {
	      if (_menuElems[i]->getString() == "Create" && this->canFinish() == true)
		return (false);
	      else
		_menuElems[i]->hover(true);
	    }
	  else
	    _menuElems[i]->hover(false);
	}
    }
  for (size_t i = 0; i < _menuElems.size(); ++i)
    _menuElems[i]->update(_clock, _input);
  return (true);
}

void		MapMenu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _menuBackground->draw(_shader, _clock);
  for (size_t i = 0; i < _menuElems.size(); ++i)
    _menuElems[i]->draw(_shader, _clock);
  for (size_t i = 0; i < _titles.size(); ++i)
    _titles[i]->draw(_shader);
  _sdlContext.flush();
}

t_game		*MapMenu::getChoice() const
{
  std::stringstream	width;
  std::stringstream	height;
  std::stringstream	nb;
  t_game		*options = new t_game;

  options->createMap = true;
  width << _menuElems[0]->getString();
  width >> options->widthMap;
  height << _menuElems[1]->getString();
  height >> options->heightMap;
  nb << _menuElems[2]->getString();
  nb >> options->playersMap;
  return (options);
}

int		MapMenu::getInfo(const std::string &fieldName) const
{
  std::string	tmp;
  std::stringstream	ss;
  int		retVal;

  retVal = -1;
  for (size_t i = 0; i < _menuElems.size(); ++i)
    {
      if (_titles[i]->getString() == fieldName)
	{
	  tmp = _menuElems[i]->getString();
	  ss << tmp;
	  ss >> retVal;
	  return (retVal);
	}
    }
  return (retVal);
}
