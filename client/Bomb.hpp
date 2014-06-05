//
// Bomb.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu Jun  5 14:21:16 2014 aurelien prieur
// Last update Thu Jun  5 16:14:35 2014 aurelien prieur
//

#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "AObject.hpp"

class	Bomb: public AObject
{
  gdl::Model	_model;
public:
  Bomb();
  virtual ~Bomb();
  virtual bool	initialize(std::pair<size_t, size_t> const &pos = (std::pair<size_t, size_t>(0, 0)));
  virtual bool	update(gdl::Clock const &clock, EventsHandler const &events);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif // !BOMB_HPP_
