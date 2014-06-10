//
// CreateMenu.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Tue Jun 10 15:52:26 2014 virol_g
// Last update Wed Jun 11 01:48:30 2014 virol_g
//

#include	<sstream>
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

  _titles.push_back(new GraphicalText("Select a map", std::pair<size_t, size_t>(400, 360),
				      glm::vec4(0.f, 0.f, 1.f, 1.f), 10, "airstrike"));
  _selectMap = new MenuScroll(std::pair<size_t, size_t>(400, 380),
  			      std::pair<size_t, size_t>(680, 380),
  			      std::pair<size_t, size_t>(80, 60),
  			      glm::vec4(0.f, 0.f, 1.f, 1.f),
  			      glm::vec4(0.93, 0.9, 0.32, 1.f));
  if (file)
    {
      while (getline(file, name))
	{
	  if (name.size() > 8)
	    name.resize(8);
	  _selectMap->addElem(new MenuButton(std::pair<size_t, size_t>(480, 380),
					    std::pair<size_t, size_t>(210, 60),
					    name, glm::vec4(0.f, 0.f, 1.f, 1.f),
					    glm::vec4(0.93, 0.9, 0.32, 1.f)));
	}
    }
  _menuBackground = new MenuBackground("./ressources/backgroundSubMenu.tga");
  _titles.push_back(new GraphicalText("How many players ?", std::pair<size_t, size_t>(400, 60),
				      glm::vec4(0.f, 0.f, 1.f, 1.f), 10, "airstrike"));
  _nbPlayers = new MenuInput(std::pair<size_t, size_t>(400, 80),
			     std::pair<size_t, size_t>(250, 60),
			     glm::vec4(1.f, 1.f, 1.f, 1.f));
  _titles.push_back(new GraphicalText("How many bots ?", std::pair<size_t, size_t>(400, 160),
				      glm::vec4(0.f, 0.f, 1.f, 1.f), 10, "airstrike"));
  _nbBots = new MenuInput(std::pair<size_t, size_t>(400, 180),
			     std::pair<size_t, size_t>(250, 60),
			     glm::vec4(1.f, 1.f, 1.f, 1.f));
  _titles.push_back(new GraphicalText("How long the game will be ?",
				      std::pair<size_t, size_t>(400, 360),
				      glm::vec4(0.f, 0.f, 1.f, 1.f), 10, "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(400, 280),
				      std::pair<size_t, size_t>(150, 40),
				      "Short", glm::vec4(0.f, 0.f, 1.f, 1.f),
				      glm::vec4(0.93, 0.9, 0.32, 1.f), "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(550, 280),
				      std::pair<size_t, size_t>(150, 60),
				      "Medium", glm::vec4(0.f, 0.f, 1.f, 1.f),
				      glm::vec4(0.93, 0.9, 0.32, 1.f), "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(700, 280),
				      std::pair<size_t, size_t>(150, 60),
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
	    }
	  if (mouse.x > _nbBots->getPos().first && mouse.x < _nbBots->getPos().first + _nbBots->getSize().first &&
	      mouse.y > _nbBots->getPos().second && mouse.y < _nbBots->getPos().second + _nbBots->getSize().second)
	    {
	      _nbBots->hover(true);
	      _nbPlayers->hover(false);
	    }
	  if (mouse.x > _nbPlayers->getPos().first && mouse.x < _nbPlayers->getPos().first + _nbPlayers->getSize().first &&
	      mouse.y > _nbPlayers->getPos().second && mouse.y < _nbPlayers->getPos().second + _nbPlayers->getSize().second)
	    {
	      _nbBots->hover(false);
	      _nbPlayers->hover(true);
	    }
	}
    }
  for (size_t i = 0; i < _menuElems.size(); ++i)
    _menuElems[i]->update(_clock, _input);
  _selectMap->update(_clock, _input);
  _nbPlayers->update(_clock, _input);
  _nbBots->update(_clock, _input);
  return (true);
}

void	CreateMenu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _menuBackground->draw(_shader, _clock);
  _nbPlayers->draw(_shader, _clock);
  _nbBots->draw(_shader, _clock);
  _selectMap->draw(_shader, _clock);
  for (size_t i = 0; i < _menuElems.size(); ++i)
    _menuElems[i]->draw(_shader, _clock);
  for (size_t i = 0; i < _titles.size(); ++i)
    _titles[i]->draw(_shader);
  _sdlContext.flush();
}

t_game		*CreateMenu::getChoice() const
{
  std::stringstream	ss;
  std::stringstream	ss2;
  t_game	*choice = new t_game;

  choice->mapName = _selectMap->getChoice();
  choice->timeGame = (_selected == -1) ? 1 : _selected;
  ss << _nbBots->getInput();
  ss >> choice->nbBots;
  ss2 << _nbPlayers->getInput();
  ss2 >> choice->nbPlayers;
  return (choice);
}
