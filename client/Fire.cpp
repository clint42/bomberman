//
// Fire.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri Jun  6 18:25:18 2014 aurelien prieur
// Last update Sat Jun  7 19:40:18 2014 aurelien prieur
//

#include "Fire.hpp"

Fire::Fire()
{
}

Fire::~Fire()
{
}

bool	Fire::initialize(std::pair<size_t, size_t> const &pos)
{
  if (_model.load("./assets/fire.fbx") == false)
    {
      std::cerr << "Couldn't load fire model" << std::endl;
      return (false);
    }
  _model.setCurrentAnim(0, true);
  this->scale(glm::vec3(0.1, 0.1, 0.1));
  this->setPos(glm::vec3(pos.first, 1, pos.second));
  return (true);
}

void	Fire::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
