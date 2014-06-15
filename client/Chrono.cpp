//
// Chrono.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat Jun  7 14:24:13 2014 aurelien prieur
// Last update Sun Jun 15 19:55:50 2014 aurelien prieur
//

#include "GraphicEngine.hpp"
#include "Chrono.hpp"

Chrono::Chrono(): _time(-1.f)
{
}

Chrono::~Chrono()
{
  delete _text;
}

bool	Chrono::initialize(std::pair<size_t, size_t> const &pos)
{
  float	origX;
  float	origY;

  (void)(pos);
  origX = (float)(W_WIDTH) / 2.f - 150.f;
  origY = 0;
  if (_texture.load("./client/assets/chronoBg.tga") == false)
    {
      std::cerr << "Couldn't load chrono background texture" << std::endl;
      return (false);
    }
  _texture.bind();
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(origX - 10.f, 0, -1));
  _geometry.pushVertex(glm::vec3(origX + 300.f, 0, -1));
  _geometry.pushVertex(glm::vec3(origX + 300.f, 70, -1));
  _geometry.pushVertex(glm::vec3(origX - 10.f, 70, -1));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.build();
  _text = new GraphicalText("0", std::pair<size_t, size_t>((W_WIDTH / 2) - 100, 0), glm::vec4(1, 1, 1, 1), 50, "airstrikeBold");
  return (true);
}

bool	Chrono::update(gdl::Clock const &clock, EventsHandler const &events)
{
  float	elapsed;

  (void)(events);
  elapsed = clock.getElapsed();
  if (_time > elapsed)
    _time -= elapsed;
  else
    _time = 0;
  buildTimeText();
  return (true);
}

void		Chrono::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)(clock);
  glViewport(0.f, 0.f, (float)(W_WIDTH), (float)(W_HEIGHT));
  glDisable(GL_DEPTH_TEST);
  _texture.bind();
  _geometry.draw(shader, glm::mat4(1), GL_QUADS);
  glEnable(GL_DEPTH_TEST);
  _text->draw(shader);
}

void			Chrono::setTime(float const &time)
{
  _time = time;
  buildTimeText();
}

float	Chrono::getTime(void) const
{
  return (_time);
}

void			Chrono::buildTimeText(void)
{
  std::ostringstream	oss;
  size_t		timeInt;
  size_t		minutes;
  size_t		seconds;

  timeInt = static_cast<size_t>(_time);
  minutes = timeInt / 60;
  seconds = timeInt % 60;
  if (minutes < 10)
    oss << "0";
  oss << minutes << ":";
  if (seconds < 10)
    oss << "0";
  oss << seconds;
  _text->updateText(oss.str());
}
