//
// Floor.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 30 17:36:18 2014 aurelien prieur
// Last update Fri May 30 17:45:31 2014 aurelien prieur
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
  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif // !FLOOR_HPP_
