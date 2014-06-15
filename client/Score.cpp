//
// Score.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Tue Jun 10 18:22:24 2014 aurelien prieur
// Last update Sun Jun 15 19:55:06 2014 aurelien prieur
//

#include "GraphicEngine.hpp"
#include "Score.hpp"

Score::Score(bool isPlayer2): _isPlayer2(isPlayer2)
{
}

Score::~Score()
{
}

bool		Score::loadTexture(void)
{
  std::string	textureName;

  if (_isPlayer2)
    textureName = "player2ScoreBg.tga";
  else
    textureName = "playerScoreBg.tga";
  if (_texture.load("./client/assets/" + textureName) == false)
    {
      std::cerr << "Coudln't load score background" << std::endl;
      return (false);
    }
  return (true);
}

bool				Score::initialize(void)
 {
  float				origX;
  std::pair<size_t, size_t>	textPos;

  origX = (_isPlayer2) ? (W_WIDTH / 2) + 360 : 280;
  if (!_isPlayer2)
    textPos = std::pair<size_t, size_t>(320, 0);
  else
    textPos = std::pair<size_t, size_t>(W_WIDTH / 2 + 400, 0);
  if (!loadTexture())
    return (false);
  _texture.bind();
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(origX, 0, -0.1));
  _geometry.pushVertex(glm::vec3(origX + 300, 0, -0.1));
  _geometry.pushVertex(glm::vec3(origX + 300, 70, -0.1));
  _geometry.pushVertex(glm::vec3(origX, 70, -0.1));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.build();
  _text = new GraphicalText("000000", textPos, glm::vec4(1, 1, 1, 1), 50, "airstrikeBold");
  _score = 0;
  return (true);
}

void			Score::update(int score)
{
  std::ostringstream	oss;
  int			i;
  int			tmpScore;

  i = 1;
  tmpScore = score;
  while ((tmpScore /= 10) > 0)
    ++i;
  for (int j = 0; j < (6 - i); ++j)
    oss <<  "0";
  oss << score;
  _text->updateText(oss.str());
  _score = score;
}

void			Score::draw(gdl::AShader &shader)
{
  glDisable(GL_DEPTH_TEST);
  _texture.bind();
  _geometry.draw(shader, glm::mat4(1), GL_QUADS);
  glEnable(GL_DEPTH_TEST);
  _text->draw(shader);
}

int			Score::getScore(void) const
{
  return (_score);
}
