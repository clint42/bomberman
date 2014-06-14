//
// ScoreWindow.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Fri Jun 13 17:46:00 2014 virol_g
// Last update Sat Jun 14 23:46:29 2014 virol_g
//

#include	"ScoreManager.hpp"
#include	"ScoreWindow.hpp"
#include	<iostream>

ScoreWindow::ScoreWindow(gdl::SdlContext &sdlContext, std::vector<int> ids,
			 std::vector<int> scores, int idWiner):
  AMenu(sdlContext), _ids(ids), _scores(scores), _idWiner(idWiner), _replay(false)
{
  _nbPlayers = (_ids[1] == -1) ? 1 : 2;
  std::cout << _nbPlayers << std::endl;
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

bool		ScoreWindow::build()
{
  bool		failed = false;

  try {
    ScoreManager	scoreManager(".bomberman.score");}

  catch (ScoreManagerException e)
    {
      failed = true;
    }
  _menuBackground = new MenuBackground("client/assets/background.tga");
  _elems.push_back(new MenuButton(std::pair<size_t, size_t>(300, 340),
				  std::pair<size_t, size_t>(140, 60),
				  "Quit", glm::vec4(0.23, 0.18, 0.52, 1.f),
				  glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _elems.push_back(new MenuButton(std::pair<size_t, size_t>(440, 340),
				  std::pair<size_t, size_t>(200, 60),
				  "Replay", glm::vec4(0.23, 0.18, 0.52, 1.f),
				  glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _text.push_back(new GraphicalText(((_ids[0] == _idWiner) ? "You won !" : "You lost..."),
				    std::pair<size_t, size_t>(400 / static_cast<size_t>(_nbPlayers), 50),
				    glm::vec4(0.23, 0.18, 0.52, 1.f), 40));
  _text.push_back(new GraphicalText(this->toString("Your score : ", _scores[0]),
				    std::pair<size_t, size_t>(400 / _nbPlayers, 80),
				    glm::vec4(0.23, 0.18, 0.52, 1.f), 30));
  if (failed == false)
    {
      ScoreManager	scoreManager(".bomberman.score");
      std::vector<int>	bestScores(scoreManager.getPlayer1Score());

      for (size_t i = 0; i < bestScores.size(); ++i)
	{
	  _text.push_back(new GraphicalText(this->toString("- ", bestScores[i]),
					    std::pair<size_t, size_t>(400 / _nbPlayers, 100 + (i * 20)),
					    glm::vec4(0.23, 0.18, 0.52, 1.f), 20));
	}
    }
  _text.push_back(new GraphicalText(((_ids[1] == _idWiner) ? "You won !" : "You lost..."),
				    std::pair<size_t, size_t>(500, 50),
				    glm::vec4(0.23, 0.18, 0.52, 1.f), 40));
  _text.push_back(new GraphicalText(this->toString("Your score : ", _scores[1]),
				    std::pair<size_t, size_t>(500, 80),
				    glm::vec4(0.23, 0.18, 0.52, 1.f), 30));
  if (failed == false)
    {
      ScoreManager	scoreManager(".bomberman.score");
      std::vector<int>	bestScores(scoreManager.getPlayer2Score());

      for (size_t i = 0; i < bestScores.size(); ++i)
	{
	  _text.push_back(new GraphicalText(this->toString("- ", bestScores[i]),
					    std::pair<size_t, size_t>(500, 100 + (i * 20)),
					    glm::vec4(0.23, 0.18, 0.52, 1.f), 20));
	}
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
