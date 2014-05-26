//
// AMenu.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 10:57:53 2014 aurelien prieur
// Last update Mon May 26 13:15:56 2014 aurelien prieur
//

#ifndef AMENU_HPP_
# define AMENU_HPP_

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
# include <vector>
# include "IMenuElem.hpp"

class	AMenu: public gdl::Game
{
  gdl::SdlContext		_sdlContext;
  gdl::Clock			_clock;
  gdl::Input			_input;
  gdl::BasicShader		_shader;
  bool				_key[2];

protected:
  std::vector<IMenuElem *>	_menuElems;
  int				_selected;
  
public:
  AMenu();
  ~AMenu();
  virtual bool	initialize();
  virtual bool	build() = 0;
  virtual bool	update();
  virtual void	draw();
  virtual void	timer();
};
#endif // !AMENU_HPP_
