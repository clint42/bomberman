//
// Player.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman_ex
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 13:07:30 2014 aurelien prieur
// Last update Sun Jun 15 06:55:59 2014 aurelien prieur
//

#include <cstdlib>
#include <iostream>
#include "Player.hpp"

gdl::Model	Player::_preloadedModel;

bool	Player::load(void)
{
  if (!_preloadedModel.load("./client/assets/marvin.fbx"))
    return (false);
  return (true);
}

Player::Player(int id): AObject(id)
{
  genColor();
}

Player::~Player()
{
}

void	Player::genColor(void)
{
  // double hue = rand() + 0.618033988749895;
  // hue -= (size_t)hue;

  // size_t hueRounded = hue * 6;
  // double saturation = 0.5;
  // double value = 0.95;
  // double f, p, q, t;

  // f = hue * 6 - hueRounded;
  // p = value * (1 - saturation);
  // q = value * (1 - f * saturation);
  // t = value * (1 - (1 - f) * saturation);

  _color.r = static_cast<float>(rand() % 255) / 255.f;
  _color.g = static_cast<float>(rand() % 255) / 255.f;
  _color.b = static_cast<float>(rand() % 255) / 255.f;
  _color.a = 1;
  // _color.r = hueRounded == 0 || hueRounded == 5 ? value
  //   : hueRounded == 1 ?                         q
  //   : hueRounded == 2 || hueRounded == 3 ?      p
  //   :   t;
  // _color.g = (hueRounded == 0 ?                     t
  // 	    : hueRounded == 1 || hueRounded == 2 ?        value
  // 	    : hueRounded == 3 ?                           q
  // 	    :     p);
  // _color.b = (hueRounded == 0 || hueRounded == 1 ? p
  // 	    : hueRounded == 3 || hueRounded == 4 ?        value
  // 	    : hueRounded == 2 ?                           t
  // 	    :     q);
  // _color.a = 1;
}

bool	Player::initialize(std::pair<size_t, size_t> const &pos)
{
  _speed = 3.0f;
  if (_model.load("./client/assets/marvin.fbx") == false)
    {
      std::cerr << "Couldn't load model." << std::endl;
      return (false);
    }
  if (_model.createSubAnim(0, "run", 25, 70) == false)
    return (false);
  if (_model.createSubAnim(0, "start", 0, 25) == false)
    return (false);
  if (_model.createSubAnim(0, "end", 75, 121) == false)
    return (false);
  this->scale(glm::vec3(0.002, 0.002, 0.002));
  this->setPos(glm::vec3(pos.first + 0.5, 0, pos.second + 0.5));
  _target.x = pos.first + 0.5;
  _target.z = pos.second + 0.5;
  return (true);
}

void	Player::updateMovement(void)
{
  if (equalVec3(_pos, _target))
    {
      if (_moveEvents.size() > 0)
  	{
  	  _direction = _moveEvents.front();
	  _moveEvents.pop_front();
	  _target = _pos + _moveVectors[_direction];
	  if (!_moving)
	    {
	      _moving = true;
	      _model.setCurrentSubAnim("start", true);
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
      std::cout << "[CLIENT] Main anim started" << std::endl;
      _model.setCurrentSubAnim("run", true);
      _mainAnimStarted = true;
    }
}

bool	Player::update(gdl::Clock const &clock, EventsHandler const &events)
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

void	Player::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  shader.setUniform("color", _color);
  _model.draw(shader, getTransformation(), clock.getElapsed());
  shader.setUniform("color", glm::vec4(1, 1, 1, 1));
}

