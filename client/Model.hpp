//
// Model.hpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman_ex
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 13:07:42 2014 aurelien prieur
// Last update Fri May 30 21:12:52 2014 aurelien prieur
//

#ifndef MODEL_HPP_
# define MODEL_HPP_

# include "AObject.hpp"
# include "EventsHandler.hpp"

class	Model: public AObject
{
  gdl::Geometry	_geometry;
  gdl::Texture	_texture;
  gdl::Model	_model;
  float		_speed;
  bool		_toDraw;
  void		setAnim(EventsHandler const &events);

public:
  Model();
  virtual ~Model();
  virtual bool	initialize();
  virtual bool	update(gdl::Clock const &clock, EventsHandler const &events);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif // !MODEL_HPP_
