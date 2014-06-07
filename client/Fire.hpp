//
// Fire.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri Jun  6 18:22:29 2014 aurelien prieur
// Last update Sat Jun  7 19:40:38 2014 aurelien prieur
//

#ifndef FIRE_HPP_
# define FIRE_HPP_

# include "AObject.hpp"

class	Fire: public AObject
{
  gdl::Model	_model;
public:
  Fire();
  virtual ~Fire();
  virtual bool	initialize(std::pair<size_t, size_t> const &pos = (std::pair<size_t, size_t>(0, 0)));
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif // !FIRE_HPP_
