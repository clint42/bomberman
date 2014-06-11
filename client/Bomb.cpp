//
// Bomb.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu Jun  5 14:24:09 2014 aurelien prieur
// Last update Wed Jun 11 13:54:09 2014 aurelien prieur
//

#include "Bomb.hpp"

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

bool	Bomb::initialize(std::pair<size_t, size_t> const &pos)
{
  if (_model.load("./client/assets/bomb.fbx") == false)
    {
      std::cerr << "Couldn't load bomb model" << std::endl;
      return (false);
    }
  this->scale(glm::vec3(0.002, 0.002, 0.002));
  this->setPos(glm::vec3(pos.first + 0.5, 0.5, pos.second + 0.5));
  return (true);
}

void	Bomb::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
