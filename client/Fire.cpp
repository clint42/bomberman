//
// Fire.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri Jun  6 18:25:18 2014 aurelien prieur
// Last update Sun Jun 15 06:56:23 2014 aurelien prieur
//

#include "Fire.hpp"

gdl::Model	Fire::_preloadedModel;

Fire::Fire(): _timeElapsed(0.0)
{
}

Fire::~Fire()
{
}

bool	Fire::load(void)
{
  if (!_preloadedModel.load("./client/assets/fire.fbx"))
    {
      std::cerr << "Couldn't load fire model" << std::endl;
      return (false);
    }
  return (true);
} 

bool	Fire::initialize(std::pair<size_t, size_t> const &pos)
{
  if (_model.load("./client/assets/fire.fbx") == false)
    {
      std::cerr << "Couldn't load fire model" << std::endl;
      return (false);
    }
  _model.setCurrentAnim(0, true);
  this->scale(glm::vec3(0.1, 0.1, 0.1));
  this->setPos(glm::vec3(pos.first + 0.5, 1, pos.second + 0.5));
  return (true);
}

bool	Fire::update(gdl::Clock const &clock, __attribute__((unused))EventsHandler const &events)
{
  (void)(events);
  _timeElapsed += clock.getElapsed();
  if (_timeElapsed > 1)
    return (false);
  else
    return (true);
}
void	Fire::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
