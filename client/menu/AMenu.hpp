//
// AMenu.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 10:57:53 2014 aurelien prieur
// Last update Tue Jun 10 19:08:56 2014 virol_g
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
  bool				_key[2];

protected:
  gdl::BasicShader		_shader;
  gdl::Clock			_clock;
  gdl::Input			_input;
  gdl::SdlContext		_sdlContext;
  IMenuElem			*_menuBackground;
  std::vector<IMenuElem *>	_menuElems;
  int				_selected;
  bool				_sdlStarted;
  
public:
  AMenu();
  ~AMenu();
  virtual bool	initialize();
  virtual bool	build() = 0;
  virtual bool	update();
  virtual void	draw();
  virtual void	timer();
  virtual gdl::SdlContext	getContext() const;
};

typedef enum	e_timeGame
  {
    SHORT,
    MEDIUM,
    LONG
  }		t_timeGame;

typedef struct	s_paramGame
{
  size_t	nbPlayers;
  size_t	serverPort;
  std::string	mapName;
  t_timeGame	timeGame;
}		t_paramGame;

#endif // !AMENU_HPP_
