//
// Model.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman_ex
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 13:07:30 2014 aurelien prieur
// Last update Sat Jun  7 19:27:15 2014 aurelien prieur
//

#include <cstdlib>
#include <iostream>
#include "Model.hpp"

Model::Model(int id): AObject(id)
{
}

Model::~Model()
{
}

float	Model::genColorComponent(void) const
{
  return (0.5);
}

bool	Model::initialize(std::pair<size_t, size_t> const &pos)
{
  _speed = 10.0f;
  if (_model.load("./assets/marvin.fbx") == false)
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

  (void)(events);
  updateMovement();
  if (_moving)
    {
      transVec = _moveVectors[_direction] * static_cast<float>(clock.getElapsed() * _speed);
      if (superiorVec3((_pos + transVec), _target, _direction))
	transVec = _target - _pos;
      translate(transVec);
    }
  return (true);
}

void	Model::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}

