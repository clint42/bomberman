//
// Model.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman_ex
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 13:07:30 2014 aurelien prieur
// Last update Thu Jun  5 15:41:31 2014 aurelien prieur
//

#include <iostream>
#include "Model.hpp"

Model::Model(int id): AObject(id)
{
}

Model::~Model()
{
}

bool	Model::initialize(std::pair<size_t, size_t> const &pos)
{
  _speed = 10.0f;
  // if (_texture.load("/home/prieur_b/LibBomberman_linux_x64/assets/marvin.fbm/Main_texture_diffuse2.tga") == false)
  //   {
  //     std::cerr << "Couldn't load texture." << std::endl;
  //     return (false);
  //   }
  if (_model.load("/home/prieur_b/LibBomberman_linux_x64/assets/marvin.fbx") == false)
    {
      std::cerr << "Couldn't load model." << std::endl;
      return (false);
    }
  if (_model.createSubAnim(0, "run", 25, 65) == false)
    return (false);
  if (_model.createSubAnim(0, "start", 0, 25) == false)
    return (false);
  if (_model.createSubAnim(0, "end", 70, 121) == false)
    return (false);
  this->scale(glm::vec3(0.002, 0.002, 0.002));
  this->setPos(glm::vec3(pos.first + 0.5, 0, pos.second + 0.5));
  _target.x = pos.first + 0.5;
  _target.z = pos.second + 0.5;
  return (true);
}

void	Model::updateMovement(void)
{
  // std::cout << "POS: " << _pos.x << " " << _pos.y << " " << _pos.z << std::endl;
  // std::cout << "TARGET: " << _target.x << " " << _target.y << " " << _target.z << std::endl;
  if (equalVec3(_pos, _target))
    {
      if (_moving)
  	_moveEvents.pop_front();
      if (_moveEvents.size() > 0)
  	{
  	  _direction = _moveEvents.front();
  	  _target = _pos + _moveVectors[_direction];
	  if (!_moving)
	    {
	      _moving = true;
	      _model.setCurrentSubAnim("start", false);
	      _mainAnimStarted = false;
	    }
  	}
      else if (_moving)
	{
	  _moving = false;
	  _model.setCurrentSubAnim("end", false);
	}
    }
  else if (_moving && !_mainAnimStarted)
    {
      _model.setCurrentSubAnim("run", true);
      _mainAnimStarted = true;
    }
}

bool	Model::update(gdl::Clock const &clock, EventsHandler const &events)
{
  glm::vec3	transVec(0, 0, 0);

  updateMovement();
  if (_moving)
    {
      transVec = _moveVectors[_direction] * static_cast<float>(clock.getElapsed() * _speed);
      if (superiorVec3((_pos + transVec), _target, _direction))
	transVec = _target - _pos;
      translate(transVec);
    }
  
  // if (_direction = EventIn::UP)
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
  //_texture.bind();
  _model.draw(shader, getTransformation(), clock.getElapsed());
}

