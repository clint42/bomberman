//
// Model.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman_ex
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 13:07:30 2014 aurelien prieur
// Last update Fri May 30 21:23:54 2014 aurelien prieur
//

#include <iostream>
#include "Model.hpp"

Model::Model()
{
}

Model::~Model()
{
}

bool	Model::initialize()
{
  _speed = 10.0f;
  if (_texture.load("/home/prieur_b/LibBomberman_linux_x64/assets/marvin.fbm/Main_texture_diffuse2.tga") == false)
    {
      std::cerr << "Couldn't load texture." << std::endl;
      return (false);
    }
  if (_model.load("/home/prieur_b/LibBomberman_linux_x64/assets/marvin.fbx") == false)
    {
      std::cerr << "Couldn't load model." << std::endl;
      return (false);
    }
  std::cout << "Texture id: " << _texture.getId() << std::endl;
  if (_model.createSubAnim(0, "run", 25, 65) == false)
    return (false);
  if (_model.createSubAnim(0, "start", 0, 25) == false)
    return (false);
  if (_model.createSubAnim(0, "end", 70, 100) == false)
    return (false);
  this->scale(glm::vec3(0.001, 0.001, 0.001));
  return (true);
}

bool	Model::update(gdl::Clock const &clock, EventsHandler const &events)
{
  // if (input.getKey(SDLK_UP))
  //   {
  //     _rotation.y = 180;
  //     translate(glm::vec3(0, 0, -0.5) * static_cast<float>(clock.getElapsed()) * _speed);
  //   }
  // if (input.getKey(SDLK_DOWN))
  //   {
  //     _model.setCurrentSubAnim("end", true);
  //     _rotation.y = 0;
  //     translate(glm::vec3(0, 0, 0.5) * static_cast<float>(clock.getElapsed()) * _speed);
  //   } 
  // if (input.getKey(SDLK_LEFT))
  //   {
      
  //     _model.setCurrentSubAnim("start", true);
  //     _rotation.y = -90;
  //     translate(glm::vec3(-0.5, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
  //   }
  // if (input.getKey(SDLK_RIGHT))
  //   {
  //      _model.setCurrentSubAnim("run", true);
  //     _rotation.y = 90;
  //     translate(glm::vec3(0.5, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
  //   }  
return (true);
}

void	Model::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _texture.bind();
  _model.draw(shader, getTransformation(), clock.getElapsed());
}

