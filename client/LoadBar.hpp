//
// LoadBar.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat Jun 14 20:03:51 2014 aurelien prieur
// Last update Sun Jun 15 01:24:25 2014 aurelien prieur
//

#ifndef LOADBAR_HPP_
# define LOADBAR_HPP_

# include <OpenGL.hh>
# include <BasicShader.hh>
# include <Geometry.hh>
# include <SdlContext.hh>
# include <Texture.hh>

class	LoadBar
{
  std::pair<float, float>	_pos;
  std::pair<float, float>	_size;
  gdl::SdlContext	&_sdlContext;
  gdl::AShader		&_shader;
  gdl::Texture		_borderTexture;
  gdl::Texture		_borderLeftTexture;
  gdl::Texture		_borderRightTexture;
  gdl::Texture		_loaderTexture;
  gdl::Geometry		_border;
  gdl::Geometry		_borderLeft;
  gdl::Geometry		_borderRight;
  gdl::Geometry		*_loaderGauge;
  void	draw(void);

public:
  LoadBar(gdl::SdlContext &sdlContext, gdl::AShader &shader);
  ~LoadBar();
  bool	initialize(std::pair<float, float> const &pos,
		   std::pair<float, float> const &size);	
  bool	update(int valueLoaded);
};

#endif // !LOADBAR_HPP_
