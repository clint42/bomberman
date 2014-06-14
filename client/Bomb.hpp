//
// Bomb.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu Jun  5 14:21:16 2014 aurelien prieur
// Last update Sat Jun 14 19:10:13 2014 aurelien prieur
//

#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "AObject.hpp"

class	Bomb: public AObject
{
  static gdl::Model	_preloadedModel;
  gdl::Model	_model;
public:
  Bomb();
  virtual ~Bomb();
  virtual bool	initialize(std::pair<size_t, size_t> const &pos = (std::pair<size_t, size_t>(0, 0)));
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  static bool load(void);
};

#endif // !BOMB_HPP_
