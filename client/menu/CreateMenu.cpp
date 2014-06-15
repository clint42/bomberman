//
// CreateMenu.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Tue Jun 10 15:52:26 2014 virol_g
// Last update Sun Jun 15 12:12:22 2014 virol_g
//

#include	<sstream>
#include	<fstream>
#include	"CreateMenu.hpp"
#include	"ReadDir.hpp"

CreateMenu::CreateMenu(gdl::SdlContext &sdlContext): AMenu(sdlContext), _createMap(false)
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
  _titles.push_back(new GraphicalText("Select a map", std::pair<size_t, size_t>(400, 410),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _selectMap = new MenuScroll(std::pair<size_t, size_t>(400, 430),
  			      std::pair<size_t, size_t>(680, 430),
  			      std::pair<size_t, size_t>(80, 50),
  			      glm::vec4(0.23, 0.18, 0.52, 1.f),
  			      glm::vec4(0.93, 0.9, 0.32, 1.f));
  while ((name = files.readFileName()) != "")
    if (name != "." && name != "..")
      _selectMap->addElem(new MenuButton(std::pair<size_t, size_t>(480, 430),
					 std::pair<size_t, size_t>(210, 50), name,
					 glm::vec4(0.23, 0.18, 0.52, 1.f),
					 glm::vec4(0.93, 0.9, 0.32, 1.f)));
  _menuBackground = new MenuBackground("./client/menu/ressources/backgroundSubMenu.tga");
  _titles.push_back(new GraphicalText("How many players ?", std::pair<size_t, size_t>(400, 110),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _inputs.push_back(new MenuInput(std::pair<size_t, size_t>(400, 130),
				  std::pair<size_t, size_t>(250, 50),
				  glm::vec4(0.23, 0.18, 0.52, 1.f), glm::vec4(0.51, 0.53, 0.85, 1.f)));
  _titles.push_back(new GraphicalText("How many bots ?", std::pair<size_t, size_t>(400, 210),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _inputs.push_back(new MenuInput(std::pair<size_t, size_t>(400, 230),
				  std::pair<size_t, size_t>(250, 50),
				  glm::vec4(0.23, 0.18, 0.52, 1.f), glm::vec4(0.51, 0.53, 0.85, 1.f)));
  _titles.push_back(new GraphicalText("Server port", std::pair<size_t, size_t>(400, 20),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _inputs.push_back(new MenuInput(std::pair<size_t, size_t>(400, 40),
				  std::pair<size_t, size_t>(250, 50),
				  glm::vec4(0.23, 0.18, 0.52, 1.f), glm::vec4(0.51, 0.53, 0.85, 1.f), "4242"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(600, 550),
				      std::pair<size_t, size_t>(200, 60),
				      "Finish", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(480, 490),
				      std::pair<size_t, size_t>(210, 50), "Gen. map",
				      glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f)));
  _titles.push_back(new GraphicalText("Game duration",
				      std::pair<size_t, size_t>(400, 310),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), P_FONT_SIZE, "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(400, 330),
				      std::pair<size_t, size_t>(135, 50),
				      "Short", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(535, 330),
				      std::pair<size_t, size_t>(150, 50),
				      "Medium", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike", true));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(685, 330),
				      std::pair<size_t, size_t>(135, 50),
				      "Long", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _selected = 3;
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
	      if (_menuElems[i]->getString() == "Gen. map" && this->canFinish() == true)
		{
		  _createMap = true;
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
  choice->mapName = _selectMap->getString();
  choice->timeGame = _selected - 1;
  ss << _inputs[0]->getString();
  ss >> choice->nbPlayers;
  ss2 << _inputs[1]->getString();
  ss2 >> choice->nbBots;
  ss3 << _inputs[2]->getString();
  ss3 >> choice->serverPort;
  choice->createMap = _createMap;
  return (choice);
}
