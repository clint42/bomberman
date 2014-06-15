//
// Fire.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri Jun  6 18:22:29 2014 aurelien prieur
// Last update Sun Jun 15 06:56:35 2014 aurelien prieur
//

#ifndef FIRE_HPP_
# define FIRE_HPP_

# include "AObject.hpp"

class	Fire: public AObject
{
  static gdl::Model	_preloadedModel;
  gdl::Model		_model;
  float			_timeElapsed;

public:
  Fire();
  virtual ~Fire();
  virtual bool	initialize(std::pair<size_t, size_t> const &pos = (std::pair<size_t, size_t>(0, 0)));
  virtual bool	update(gdl::Clock const &clock, EventsHandler const &events);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  static  bool  load(void);
};

#endif // !FIRE_HPP_
