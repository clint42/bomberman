//
// AObject.hpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman_ex
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 11:05:44 2014 aurelien prieur
// Last update Fri May 30 20:48:29 2014 aurelien prieur
//

#ifndef AOBJECT_HPP_
# define AOBJECT_HPP_

# include <OpenGL.hh>
# include <Game.hh>
# include <Clock.hh>
# include <Input.hh>
# include <SdlContext.hh>
# include <Geometry.hh>
# include <Texture.hh>
# include <BasicShader.hh>
# include <Model.hh>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include "EventsHandler.hpp"

enum	ObjectType
  {
    PLAYER
  };

class	AObject
{
protected:
  glm::vec3	_pos;
  glm::vec3	_rotation;
  glm::vec3	_scale;

public:
  AObject();
  virtual	~AObject();
  virtual bool	initialize();
  virtual bool	update(gdl::Clock const &clock, EventsHandler const &events);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;

  void		translate(glm::vec3 const &v);
  void		rotate(glm::vec3 const &axis, float angle);
  void		scale(glm::vec3 const &scale);
  glm::mat4	getTransformation();
  void		setPos(glm::vec3 const &pos);
  void		setScale(glm::vec3 const &scale);
  static AObject	*create(ObjectType type);
};

#endif // !AOBJECT_HPP_
