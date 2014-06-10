//
// FpsDisplay.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Tue Jun 10 12:03:41 2014 aurelien prieur
// Last update Tue Jun 10 12:21:30 2014 aurelien prieur
//

#include <sstream>
#include "FpsDisplay.hpp"

FpsDisplay::FpsDisplay(): _timer(0), _fps(0)
{
  _text = new GraphicalText("FPS: 0", std::pair<size_t, size_t>(10, 10), glm::vec4(1, 0, 0, 1), 50, "quartzMs");
}

FpsDisplay::~FpsDisplay()
{
  delete _text;
}

void	FpsDisplay::updateTimer(float const &time)
{
  _timer += time;
}

void			FpsDisplay::draw(gdl::AShader &shader)
{
  std::ostringstream	oss;

  ++_fps;
  if (_timer > 1)
    {
      oss << "FPS: " << _fps;
      _text->updateText(oss.str());
      _fps = 0;
      _timer = 0;
    }
  _text->draw(shader);
}
