//
// Intro.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client/menu
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sun Jun 15 21:02:33 2014 aurelien prieur
// Last update Sun Jun 15 21:44:21 2014 aurelien prieur
//

#ifndef INTRO_HPP_
# define INTRO_HPP_

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
# include <iostream>
# include "../GraphicalText.hpp"

class	Intro
{
  float			_elapsedTime;
  int			_lastTextDisplayed;
  bool			_isFinished;
  gdl::BasicShader	_shader;
  gdl::Clock		_clock;
  gdl::Input		_input;
  gdl::SdlContext	*_sdlContext;
  gdl::Texture		_backgroundTex;
  gdl::Geometry		_background;
  std::vector<GraphicalText *>	_texts;
public:
  Intro(gdl::SdlContext *sdlContext);
  ~Intro();
  bool	initialize();
  bool	update();
  void	draw();
  bool	isFinished() const;
};

#endif // !INTRO_HPP_
