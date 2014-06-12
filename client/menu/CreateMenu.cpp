//
// CreateMenu.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Tue Jun 10 15:52:26 2014 virol_g
// Last update Thu Jun 12 18:32:31 2014 virol_g
//

#include	<sstream>
#include	<fstream>
#include	"CreateMenu.hpp"

CreateMenu::CreateMenu(gdl::SdlContext &sdlContext): AMenu(sdlContext)
{
  //_sdlContext = sdlContext;
  // _sdlStarted = true;
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
  std::ifstream	file("./client/maps");
  std::string	name;

  if (!file)
    {
      std::cerr << "Unable to open maps list file" << std::endl;
      return (false);
    }
  _titles.push_back(new GraphicalText("Select a map", std::pair<size_t, size_t>(400, 360),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _selectMap = new MenuScroll(std::pair<size_t, size_t>(400, 380),
  			      std::pair<size_t, size_t>(680, 380),
  			      std::pair<size_t, size_t>(80, 60),
  			      glm::vec4(0.23, 0.18, 0.52, 1.f),
  			      glm::vec4(0.93, 0.9, 0.32, 1.f));
  while (getline(file, name))
    {
      _selectMap->addElem(new MenuButton(std::pair<size_t, size_t>(480, 380),
					 std::pair<size_t, size_t>(210, 60), name,
					 glm::vec4(0.23, 0.18, 0.52, 1.f),
					 glm::vec4(0.93, 0.9, 0.32, 1.f)));
    }
  _menuBackground = new MenuBackground("./client/menu/ressources/backgroundSubMenu.tga");
  _titles.push_back(new GraphicalText("How many players ?", std::pair<size_t, size_t>(400, 60),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _nbPlayers = new MenuInput(std::pair<size_t, size_t>(400, 80), std::pair<size_t, size_t>(250, 60),
			     glm::vec4(0.23, 0.18, 0.52, 1.f), glm::vec4(0.51, 0.53, 0.85, 1.f));
  _titles.push_back(new GraphicalText("How many bots ?", std::pair<size_t, size_t>(400, 160),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _nbBots = new MenuInput(std::pair<size_t, size_t>(400, 180), std::pair<size_t, size_t>(250, 60),
			  glm::vec4(0.23, 0.18, 0.52, 1.f), glm::vec4(0.51, 0.53, 0.85, 1.f));
  _titles.push_back(new GraphicalText("Game duration",
				      std::pair<size_t, size_t>(400, 260),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(570, 500),
				      std::pair<size_t, size_t>(200, 60),
				      "Finish", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(400, 280),
				      std::pair<size_t, size_t>(135, 50),
				      "Short", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(535, 280),
				      std::pair<size_t, size_t>(150, 50),
				      "Medium", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike", true));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(685, 280),
				      std::pair<size_t, size_t>(135, 50),
				      "Long", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
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
	      if (_menuElems[i]->getString() == "Finish" && _nbBots->getString() != "" && _nbPlayers->getString() != "")
		return (false);
	      if (i != static_cast<size_t>(_selected))
		{
		  _menuElems[_selected]->hover(false);
		}
	      _selected = i;
	      _menuElems[i]->hover(true);
	    }
	  if (static_cast<size_t>(mouse.x) > _nbBots->getPos().first &&
	      static_cast<size_t>(mouse.x) < _nbBots->getPos().first + _nbBots->getSize().first &&
	      static_cast<size_t>(mouse.y) > _nbBots->getPos().second &&
	      static_cast<size_t>(mouse.y) < _nbBots->getPos().second + _nbBots->getSize().second)
	    {
	      _nbBots->hover(true);
	      _nbPlayers->hover(false);
	    }
	  if (static_cast<size_t>(mouse.x) > _nbPlayers->getPos().first &&
	      static_cast<size_t>(mouse.x) < _nbPlayers->getPos().first + _nbPlayers->getSize().first &&
	      static_cast<size_t>(mouse.y) > _nbPlayers->getPos().second &&
	      static_cast<size_t>(mouse.y) < _nbPlayers->getPos().second + _nbPlayers->getSize().second)
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

  if (_selected == -1)
    return (NULL);
  std::cout << "Create menu getChoice !" << std::endl;
  choice->mapName = _selectMap->getString();
  std::cout << "AFter select map getChoice." << std::endl;
  choice->timeGame = (_selected == -1) ? 2 : _selected;
  ss << _nbBots->getString();
  ss >> choice->nbBots;
  ss2 << _nbPlayers->getString();
  ss2 >> choice->nbPlayers;
  return (choice);
}
