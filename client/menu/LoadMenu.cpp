//
// LoadMenu.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Sun Jun 15 10:47:18 2014 virol_g
// Last update Sun Jun 15 12:32:22 2014 virol_g
//

#include	"LoadMenu.hpp"

LoadMenu::LoadMenu(gdl::SdlContext &sdlContext) : AMenu(sdlContext)
{
}

LoadMenu::~LoadMenu()
{
  delete _files;
  delete _menuBackground;
  delete _portInput;
  for (size_t i = 0; i < _titles.size(); ++i)
    delete _titles[i];
}

bool	LoadMenu::build()
{
  ReadDir	files("./save");
  std::string	name;

  if (files.initialize() == false)
    {
      std::cerr << "Unable to open save file." << std::endl;
      return (false);
    }
  _menuBackground = new MenuBackground("./client/menu/ressources/backgroundSubMenu.tga");
  _titles.push_back(new GraphicalText("Select a game", std::pair<size_t, size_t>(400, 200),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), 20, "airstrike"));
  _files = new MenuScroll(std::pair<size_t, size_t>(400, 220),
			  std::pair<size_t, size_t>(680, 220),
			  std::pair<size_t, size_t>(80, 50),
			  glm::vec4(0.23, 0.18, 0.52, 1.f),
			  glm::vec4(0.93, 0.9, 0.32, 1.f));
  while ((name = files.readFileName()) != "")
    if (name != "." && name != "..")
      _files->addElem(new MenuButton(std::pair<size_t, size_t>(480, 220),
				     std::pair<size_t, size_t>(210, 50), name,
				     glm::vec4(0.23, 0.18, 0.52, 1.f),
				     glm::vec4(0.93, 0.9, 0.32, 1.f)));
  _portInput = new MenuInput(std::pair<size_t, size_t>(400, 370),
				     std::pair<size_t, size_t>(250, 50),
				     glm::vec4(0.23, 0.18, 0.52, 1.f),
				     glm::vec4(0.51, 0.53, 0.85, 1.f));
  _titles.push_back(new GraphicalText("Server port", std::pair<size_t, size_t>(400, 350),
				      glm::vec4(0.23, 0.18, 0.52, 1.f), 20, "airstrike"));
  _menuElems.push_back(new MenuButton(std::pair<size_t, size_t>(600, 550),
				      std::pair<size_t, size_t>(200, 60),
				      "Load", glm::vec4(0.23, 0.18, 0.52, 1.f),
				      glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  return (true);
}

bool	LoadMenu::canFinish() const
{
  if (_portInput->getString() == "")
    return (false);
  return (true);
}

bool	LoadMenu::update()
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
      if (static_cast<size_t>(mouse.x) > _menuElems[0]->getPos().first &&
	  static_cast<size_t>(mouse.x) < _menuElems[0]->getPos().first + _menuElems[0]->getSize().first &&
	  static_cast<size_t>(mouse.y) > _menuElems[0]->getPos().second &&
	  static_cast<size_t>(mouse.y) < _menuElems[0]->getPos().second + _menuElems[0]->getSize().second && this->canFinish() == true)
	return (false);
      if (static_cast<size_t>(mouse.x) > _portInput->getPos().first &&
	  static_cast<size_t>(mouse.x) < _portInput->getPos().first + _portInput->getSize().first &&
	  static_cast<size_t>(mouse.y) > _portInput->getPos().second &&
	  static_cast<size_t>(mouse.y) < _portInput->getPos().second + _portInput->getSize().second)
	_portInput->hover(true);
      else
	_portInput->hover(false);
    }
  _portInput->update(_clock, _input);
  _menuElems[0]->update(_clock, _input);
  _files->update(_clock, _input);
  return (true);
}

void	LoadMenu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _menuBackground->draw(_shader, _clock);
  _portInput->draw(_shader, _clock);
  _menuElems[0]->draw(_shader, _clock);
  for (size_t i = 0; i < _titles.size(); ++i)
    _titles[i]->draw(_shader);
  _sdlContext.flush();
}

t_game	*LoadMenu::getChoice() const
{
  std::stringstream	ss;
  t_game	*choice = new t_game;

  if (_selected == -1)
    return (NULL);
  choice->loadMap = true;
  ss << _portInput->getString();
  ss >> choice->serverPort;
  choice->mapName = _files->getString();
  return (choice);
}
