//
// Model.hpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman_ex
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 13:07:42 2014 aurelien prieur
// Last update Mon May 12 18:24:38 2014 aurelien prieur
//

#ifndef MODEL_HPP_
# define MODEL_HPP_

# include "AObject.hpp"

class	Model: public AObject
{
  gdl::Geometry	_geometry;
  gdl::Texture	_texture;
  gdl::Model	_model;
  float		_speed;
  bool		_toDraw;
public:
  Model();
  virtual ~Model();
  virtual bool	initialize();
  virtual bool	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shadeer, gdl::Clock const &clock);
};

#endif // !MODEL_HPP_
