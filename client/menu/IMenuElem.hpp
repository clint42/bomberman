//
// MenuElem.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 11:18:47 2014 aurelien prieur
// Last update Sat Jun  7 15:19:12 2014 virol_g
//

#ifndef MENUELEM_HPP_
# define MENUELEM_HPP_

#include <OpenGL.hh>
#include <Game.hh>
#include <Clock.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <Geometry.hh>
#include <Texture.hh>
#include <BasicShader.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>

class				IMenuElem
{
public:
  virtual ~IMenuElem() {};
  virtual bool	initialize(std::string const &textureName) = 0;
  virtual bool	update(gdl::Clock const &clock, gdl::Input &input) = 0;
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;
  virtual void	hover(bool isHover) = 0;

  virtual std::pair<size_t, size_t>	getPos() const = 0;
  virtual std::pair<size_t, size_t>	getSize() const = 0;
};

#endif // !MENUELEM_HPP_
