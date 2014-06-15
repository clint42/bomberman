//
// ScoreWindow.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Fri Jun 13 17:46:00 2014 virol_g
// Last update Sun Jun 15 09:35:09 2014 virol_g
//

#include	"ScoreWindow.hpp"
#include	<iostream>

ScoreWindow::ScoreWindow(gdl::SdlContext &sdlContext, std::vector<int> ids,
			 std::vector<int> scores, int idWiner):
  AMenu(sdlContext), _ids(ids), _scores(scores), _idWiner(idWiner), _replay(false)
{
  _nbPlayers = (_ids[1] == -1) ? 1 : 2;
}

ScoreWindow::~ScoreWindow()
{
  delete _menuBackground;
  for (size_t i = 0; i < _elems.size(); ++i)
    delete _elems[i];
  for (size_t i = 0; i < _text.size(); ++i)
    delete _text[i];
}

std::string	ScoreWindow::toString(const std::string &str, int nb)
{
  std::stringstream	ss;
  std::string		tmp;
  std::string		ret;

  ret = str;
  ss << nb;
  ss >> tmp;
  ret += tmp;
  return (ret);
}

bool		ScoreWindow::initialize()
{
  glm::mat4     projection;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!_shader.load("./client/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./client/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    {
      std::cerr << "Shader loading error" << std::endl;
      return (false);
    }
  projection = glm::ortho(0.f, 1920.f, 1080.f, 0.f, -1.f, 1.f);
  _shader.bind();
  _shader.setUniform("projection", projection);
  _shader.setUniform("view", glm::mat4(1));
  return (true);
}

bool		ScoreWindow::build()
{
  _scoreManager = new ScoreManager(".bomberman.score");

  _menuBackground = new MenuBackground("client/menu/ressources/whiteTex.tga", 1920, 1080);
  _elems.push_back(new MenuButton(std::pair<size_t, size_t>(820, 980),
				  std::pair<size_t, size_t>(140, 60),
				  "Quit", glm::vec4(0.23, 0.18, 0.52, 1.f),
				  glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _elems.push_back(new MenuButton(std::pair<size_t, size_t>(960, 980),
				  std::pair<size_t, size_t>(200, 60),
				  "Replay", glm::vec4(0.23, 0.18, 0.52, 1.f),
				  glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _text.push_back(new GraphicalText(((_ids[0] == _idWiner) ? "You won !" : "You lost..."),
				    std::pair<size_t, size_t>(500 / static_cast<size_t>(_nbPlayers), 50),
				    glm::vec4(0.23, 0.18, 0.52, 1.f), 60));
  _text.push_back(new GraphicalText(this->toString("Your score : ", _scores[0]),
				    std::pair<size_t, size_t>(500 / _nbPlayers, 150),
				    glm::vec4(0.23, 0.18, 0.52, 1.f), 50));
  std::vector<int>	bestScores(_scoreManager->getPlayer1Score());

  _text.push_back(new GraphicalText("Your best scores :",
				    std::pair<size_t, size_t>(500 / _nbPlayers, 300),
				    glm::vec4(0.23, 0.18, 0.52, 1.f), 40));
  for (size_t i = 0; i < bestScores.size(); ++i)
    {
      _text.push_back(new GraphicalText(this->toString("- ", bestScores[i]),
					std::pair<size_t, size_t>(500 / _nbPlayers, 400 + (i * 40)),
					glm::vec4(0.23, 0.18, 0.52, 1.f), 40));
    }
  _scoreManager->addPlayer1Score(_scores[0]);
  _scoreManager->save();
  if (_nbPlayers == 2)
    {
      _text.push_back(new GraphicalText(((_ids[1] == _idWiner) ? "You won !" : "You lost..."),
					std::pair<size_t, size_t>(1200, 50),
					glm::vec4(0.23, 0.18, 0.52, 1.f), 60));
      _text.push_back(new GraphicalText(this->toString("Your score : ", _scores[1]),
					std::pair<size_t, size_t>(1200, 150),
					glm::vec4(0.23, 0.18, 0.52, 1.f), 50));
      std::vector<int>	bestScores(_scoreManager->getPlayer2Score());
      
      _text.push_back(new GraphicalText("Your best scores :",
					std::pair<size_t, size_t>(1200, 300),
					glm::vec4(0.23, 0.18, 0.52, 1.f), 40));
      for (size_t i = 0; i < bestScores.size(); ++i)
	{
	  _text.push_back(new GraphicalText(this->toString("- ", bestScores[i]),
					    std::pair<size_t, size_t>(1200, 400 + (i * 40)),
					    glm::vec4(0.23, 0.18, 0.52, 1.f), 40));
	}
      _scoreManager->addPlayer2Score(_scores[1]);
      _scoreManager->save();
    }
  return (true);
}

bool		ScoreWindow::update()
{
  glm::ivec2	mouse;

  this->_sdlContext.updateClock(this->_clock);
  this->_sdlContext.updateInputs(this->_input);
  if (this->_input.getKey(SDLK_ESCAPE) || this->_input.getInput(SDL_QUIT, false))
    {
      _replay = false;
      return (false);
    }
  if (this->_input.getKey(SDL_BUTTON_LEFT))
    {
      mouse = this->_input.getMousePosition();
      for (size_t i = 0; i < _elems.size(); ++i)
	{
	  if (static_cast<size_t>(mouse.x) > _elems[i]->getPos().first &&
	      static_cast<size_t>(mouse.x) < _elems[i]->getPos().first + _elems[i]->getSize().first &&
	      static_cast<size_t>(mouse.y) > _elems[i]->getPos().second &&
	      static_cast<size_t>(mouse.y) < _elems[i]->getPos().second + _elems[i]->getSize().second)
	    {
	      if (_elems[i]->getString() == "Replay")
		_replay = true;
	      return (false);
	    }
	}
    }
  for (size_t i = 0; i < _elems.size(); ++i)
    _elems[i]->update(_clock, _input);
  return (true);
}

void		ScoreWindow::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
   _menuBackground->draw(_shader, _clock);
  for (size_t i = 0; i < _elems.size(); ++i)
    _elems[i]->draw(_shader, _clock);
  for (size_t i = 0; i < _text.size(); ++i)
    _text[i]->draw(_shader);
  _sdlContext.flush();
}

bool		ScoreWindow::replay() const
{
  return (_replay);
}

t_game		*ScoreWindow::getChoice() const
{
  return (NULL);
}
