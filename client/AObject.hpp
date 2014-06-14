//
// AObject.hpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman_ex
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 11:05:44 2014 aurelien prieur
// Last update Sat Jun 14 12:22:08 2014 aurelien prieur
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
# include <list>
# include "EventsHandler.hpp"

//PLAYER must be the last of ObjectType enum
enum	ObjectType
  {
    VOID,
    BLOCK,
    BOMB,
    FIRE,
    BOX,
    BONUSSPEED,
    BONUSRANGE,
    BONUSBOMB,
    PLAYER
  };

class	AObject
{
public:
  enum	EventIn
    {
      DOWN = 0,
      RIGHT = 1,
      UP = 2,
      LEFT = 3
    };
protected:
  int				_id;
  glm::vec3			_pos;
  glm::vec3			_rotation;
  glm::vec3			_nextRotation;
  bool				_hasNextRotation;
  glm::vec3			_scale;
  glm::vec3			_target;
  EventIn			_direction;
  bool				_moving;
  std::list<EventIn>		_moveEvents;
  std::vector<glm::vec3>	_moveVectors;	
  bool		equalVec3(glm::vec3 const &vec1, glm::vec3 const &vec2);
  bool		superiorVec3(glm::vec3 const &vec1, glm::vec3 const &vec2, EventIn direction);

public:
  AObject();
  AObject(int id);
  virtual	~AObject();
  virtual bool	initialize(std::pair<size_t, size_t> const &pos = (std::pair<size_t, size_t>(0, 0)));
  virtual bool	update(gdl::Clock const &clock, EventsHandler const &events);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;
  void			translate(glm::vec3 const &v);
  void			rotate(glm::vec3 const &axis, float angle);
  void			scale(glm::vec3 const &scale);
  glm::mat4		getTransformation();
  void			setPos(glm::vec3 const &pos);
  glm::vec3 const	&getPos(void) const;
  void			setScale(glm::vec3 const &scale);
  void			setRotation(glm::vec3 const &rotation);
  glm::vec3	const	&getRotation() const;
  void			addMoveEvent(EventIn event);
  int			getId(void) const;
  static AObject	*create(int objectType);
};

#endif // !AOBJECT_HPP_
