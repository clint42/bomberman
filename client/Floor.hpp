//
// Floor.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 30 17:36:18 2014 aurelien prieur
// Last update Sat Jun  7 19:19:20 2014 aurelien prieur
//

#ifndef FLOOR_HPP_
# define FLOOR_HPP_

# include "AObject.hpp"

class	Floor: public AObject
{
  std::pair<double, double>  _size;
  gdl::Geometry	_geometry;
  gdl::Texture	_texture;

public:
  Floor(std::pair<size_t, size_t> const &size);
  virtual ~Floor();
  virtual bool	initialize(std::pair<size_t, size_t> const &pos = (std::pair<size_t, size_t>(0, 0)));
  virtual bool	update(gdl::Clock const &clock, EventsHandler const &events);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif // !FLOOR_HPP_
