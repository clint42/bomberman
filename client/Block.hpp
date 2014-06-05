//
// Block.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client/menu
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu Jun  5 12:04:53 2014 aurelien prieur
// Last update Thu Jun  5 13:49:20 2014 aurelien prieur
//

#ifndef BLOCK_HPP_
# define BLOCK_HPP_

# include "AObject.hpp"

class	Block: public AObject
{
  gdl::Geometry	_geometry;
  gdl::Texture	_texture;
  
public:
  Block();
  virtual ~Block();
  virtual bool	initialize(std::pair<size_t, size_t> const &pos = (std::pair<size_t, size_t>(0, 0)));
  virtual bool	update(gdl::Clock const &clock, EventsHandler const &events);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif // !BLOCK_HPP_
