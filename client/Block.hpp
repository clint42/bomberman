//
// Block.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client/menu
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu Jun  5 12:04:53 2014 aurelien prieur
// Last update Sun Jun 15 07:16:05 2014 aurelien prieur
//

#ifndef BLOCK_HPP_
# define BLOCK_HPP_

# include <map>
# include <utility>
# include "AObject.hpp"

class	Block: public AObject
{
  float						_timeElapsed;
  ObjectType					_blockType;
  gdl::Geometry					_geometry;
  static std::map<ObjectType, gdl::Texture *>	textures;

public:
  Block(ObjectType blockType = BLOCK);
  virtual ~Block();
  virtual bool	initialize(std::pair<size_t, size_t> const &pos = (std::pair<size_t, size_t>(0, 0)));
  virtual bool	update(gdl::Clock const &clock, EventsHandler const &events);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  static bool	loadTextures(void);
};

#endif // !BLOCK_HPP_
