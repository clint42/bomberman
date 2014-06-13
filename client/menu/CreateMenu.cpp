//
// CreateMenu.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Tue Jun 10 15:52:26 2014 virol_g
// Last update Fri Jun 13 14:31:33 2014 virol_g
//

#include	<sstream>
#include	<fstream>
#include	"CreateMenu.hpp"
#include	"ReadDir.hpp"

CreateMenu::CreateMenu(gdl::SdlContext &sdlContext): AMenu(sdlContext)
{
}

CreateMenu::~CreateMenu()
{
  delete _menuBackground;
  delete _selectMap;
  for (size_t i = 0; i < _inputs.size(); ++i)
    delete _inputs[i];
  for (size_t i = 0; i < _menuElems.size(); ++i)
    delete _menuElems[i];
}

bool	CreateMenu::build()
{
  ReadDir	files("./maps");
  std::string	name;

  if (files.initialize() == false)
    {
      std::cerr << "Unable to open maps list file" << std::endl;
      return (false);
    }
  _titles.push_back(new GraphicalText("Select a map", std::pair<size_t, size_t>(400, 440),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _selectMap = new MenuScroll(std::pair<size_t, size_t>(400, 460),
  			      std::pair<size_t, size_t>(680, 460),
  			      std::pair<size_t, size_t>(80, 60),
  			      glm::vec4(0.23, 0.18, 0.52, 1.f),
  			      glm::vec4(0.93, 0.9, 0.32, 1.f));
  while ((name = files.readFileName()) != "")
    if (name != "." && name != "..")
      _selectMap->addElem(new MenuButton(std::pair<size_t, size_t>(480, 460),
					 std::pair<size_t, size_t>(210, 60), name,
					 glm::vec4(0.23, 0.18, 0.52, 1.f),
					 glm::vec4(0.93, 0.9, 0.32, 1.f)));
  _menuBackground = new MenuBackground("./client/menu/ressources/backgroundSubMenu.tga");
  _titles.push_back(new GraphicalText("How many players ?", std::pair<size_t, size_t>(400, 120),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _inputs.push_back(new MenuInput(std::pair<size_t, size_t>(400, 140),
				  std::pair<size_t, size_t>(250, 60),
				  glm::vec4(0.23, 0.18, 0.52, 1.f), glm::vec4(0.51, 0.53, 0.85, 1.f)));
  _titles.push_back(new GraphicalText("How many bots ?", std::pair<size_t, size_t>(400, 240),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _inputs.push_back(new MenuInput(std::pair<size_t, size_t>(400, 260),
				  std::pair<size_t, size_t>(250, 60),
				  glm::vec4(0.23, 0.18, 0.52, 1.f), glm::vec4(0.51, 0.53, 0.85, 1.f)));

  _titles.push_back(new GraphicalText("Server port", std::pair<size_t, size_t>(400, 20),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _inputs.push_back(new MenuInput(std::pair<size_t, size_t>(400, 40), std::pair<size_t, size_t>(250, 60),
				  glm::vec4(0.23, 0.18, 0.52, 1.f), glm::vec4(0.51, 0.53, 0.85, 1.f)));

  _titles.push_back(new GraphicalText("Game duration",
				      std::pair<size_t, size_t>(400, 340),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));

  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(600, 550),
				      std::pair<size_t, size_t>(200, 60),
				      "Finish", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));

  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(400, 360),
				      std::pair<size_t, size_t>(135, 50),
				      "Short", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(535, 360),
				      std::pair<size_t, size_t>(150, 50),
				      "Medium", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike", true));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(685, 360),
				      std::pair<size_t, size_t>(135, 50),
				      "Long", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _selected = 2;
  return (true);
}

bool	CreateMenu::canFinish() const
{
  for (size_t i = 0; i < _inputs.size(); ++i)
    {
      if (_inputs[i]->getString() == "")
	return (false);
    }
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
	      if (i != static_cast<size_t>(_selected))
		_menuElems[_selected]->hover(false);
	      if (_menuElems[i]->getString() == "Finish")
		{
		  i = _selected;
		  if (this->canFinish() == true)
		    return (false);
		}
	      _selected = i;
	      _menuElems[i]->hover(true);
	    }
	  for (size_t i = 0; i < _inputs.size(); ++i)
	    {
	      if (static_cast<size_t>(mouse.x) > _inputs[i]->getPos().first &&
		  static_cast<size_t>(mouse.x) < _inputs[i]->getPos().first + _inputs[i]->getSize().first &&
		  static_cast<size_t>(mouse.y) > _inputs[i]->getPos().second &&
		  static_cast<size_t>(mouse.y) < _inputs[i]->getPos().second + _inputs[i]->getSize().second)
		_inputs[i]->hover(true);
	      else
		_inputs[i]->hover(false);
	    }
	}
    }
  for (size_t i = 0; i < _menuElems.size(); ++i)
    _menuElems[i]->update(_clock, _input);
  _selectMap->update(_clock, _input);
  for (size_t i = 0; i < _inputs.size(); ++i)
    _inputs[i]->update(_clock, _input);
  return (true);
}

void	CreateMenu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _menuBackground->draw(_shader, _clock);
  for (size_t i = 0; i < _inputs.size(); ++i)
    _inputs[i]->draw(_shader, _clock);
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
  std::stringstream	ss3;
  t_game	*choice = new t_game;

  if (_selected == -1)
    return (NULL);
  std::cout << "Create menu getChoice !" << std::endl;
  choice->mapName = _selectMap->getString();
  std::cout << "AFter select map getChoice." << std::endl;
  choice->timeGame = (_selected == -1) ? 2 : _selected;
  ss << _inputs[0]->getString();
  ss >> choice->nbPlayers;
  ss2 << _inputs[1]->getString();
  ss2 >> choice->nbBots;
  ss3 << _inputs[2]->getString();
  ss3 >> choice->serverPort;
  return (choice);
}
