//
// Bonus.hpp for Bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat Jun 14 11:48:12 2014 aurelien prieur
// Last update Sat Jun 14 12:36:05 2014 aurelien prieur
//

#ifndef BONUS_HPP_
# define BONUS_HPP_

# include "AObject.hpp"

class	Bonus: public AObject
{
  ObjectType					_bonusType;
  gdl::Geometry					_geometry;
  static std::map<ObjectType, gdl::Texture *>	_textures;

public:
  Bonus(ObjectType bonusType);
  virtual ~Bonus();
  virtual bool initialize(std::pair<size_t, size_t> const &pos = (std::pair<size_t, size_t>(0, 0)));
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);
  static bool	loadTextures(void);
};

#endif // !BONUS_HPP_
