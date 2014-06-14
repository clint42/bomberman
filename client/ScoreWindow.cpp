//
// ScoreWindow.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Fri Jun 13 17:46:00 2014 virol_g
// Last update Sat Jun 14 17:46:27 2014 virol_g
//

#include	"ScoreManager.hpp"
#include	"ScoreWindow.hpp"

ScoreWindow::ScoreWindow(std::vector<int> ids, std::vector<int> scores,
	    gdl::SdlContext sdlContext, int idWiner):
  AMenu(sdlContext), _ids(ids), _scores(scores), _idWiner(idWiner)
{
  _nbPlayers = (_ids[1] == -1) ? 1 : 2;
}

ScoreWindow::~ScoreWindow()
{
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
  ScoreManager	scoreManager(".bomberman.score");
  std::vector<int>	bestScores(scoreManager.getPlayer1Score());

  (void)_idWiner;
  (void)scoreManager;
  _elems.push_back(new MenuButton(std::pair<size_t, size_t>(300, 540),
				  std::pair<size_t, size_t>(100, 60),
				  "Quit", glm::vec4(0.23, 0.18, 0.52, 1.f),
				  glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  _elems.push_back(new MenuButton(std::pair<size_t, size_t>(300, 540),
				  std::pair<size_t, size_t>(100, 60),
				  "Replay", glm::vec4(0.23, 0.18, 0.52, 1.f),
				  glm::vec4(0.51, 0.53, 0.85, 1.f), "airstrike"));
  // PLAYER 1
  _text.push_back(new GraphicalText(((_ids[0] == _idWiner) ? "You won !" : "You lost..."),
				    std::pair<size_t, size_t>(400 / static_cast<size_t>(_nbPlayers), 50),
				    glm::vec4(0.23, 0.18, 0.52, 1.f), 40));
  _text.push_back(new GraphicalText(this->toString("Your score : ", _scores[0]),
				    std::pair<size_t, size_t>(400 / _nbPlayers, 80),
				    glm::vec4(0.23, 0.18, 0.52, 1.f), 30));
  for (size_t i = 0; i < bestScores.size(); ++i)
    {
      _text.push_back(new GraphicalText(this->toString("- ", bestScores[i]),
					std::pair<size_t, size_t>(400 / _nbPlayers, 100 + (i * 20)),
					glm::vec4(0.23, 0.18, 0.52, 1.f), 20));
    }
  return (true);
}
