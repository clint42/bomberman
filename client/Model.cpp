//
// Model.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman_ex
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 13:07:30 2014 aurelien prieur
// Last update Fri May 23 14:17:07 2014 virol_g
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
  if (_texture.load("./assets/marvin.fbm/Main_texture_diffuse2.tga") == false)
    {
      std::cerr << "Couldn't load texture." << std::endl;
      return (false);
    }
  if (_model.load("./assets/marvin.fbx") == false)
    {
      std::cerr << "Couldn't load model." << std::endl;
      return (false);
    }
  if (_model.createSubAnim(0, "run", 0, 60) == false)
    return (false);
  return (true);
}

bool	Model::update(gdl::Clock const &clock, gdl::Input &input)
{
  std::cout << "UPDATE MODEL" << std::endl;
  if (input.getKey(SDLK_UP))
    {
      _rotation.y = 180;
      translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
    }
  if (input.getKey(SDLK_DOWN))
    {
      _model.setCurrentAnim(0, true);
      _rotation.y = 0;
      translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
    } 
  if (input.getKey(SDLK_LEFT))
    {
      
      _model.setCurrentAnim(0, true);
      _rotation.y = -90;
      translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    }
  if (input.getKey(SDLK_RIGHT))
    {
       _model.setCurrentAnim("run", true);
      _rotation.y = 90;
      translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    }  
return (true);
}

void	Model::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _texture.bind();
  _model.draw(shader, getTransformation(), clock.getElapsed());
}

