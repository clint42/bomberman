//
// GraphicalLetter.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 13:20:15 2014 aurelien prieur
// Last update Sat May 24 15:14:28 2014 aurelien prieur
//

#ifndef GRAPHICALLETTER_HPP_
# define GRAPHICALLETTER_HPP_

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
# include <utility>

class	GraphicalLetter
{
  gdl::Texture	const		&_abcTex;
  gdl::Geometry			_geometry;
  std::pair<size_t, size_t>	_pos;
  float				_fontSize;
  glm::vec4			_color;
public:
  GraphicalLetter(char letter, std::pair<size_t, size_t> const &pos,
		  glm::vec4 const &color,
		  float const &fontSize,
		  gdl::Texture const &texture);
  ~GraphicalLetter();
  void	draw(gdl::AShader &shader);
  void	updateColor(glm::vec4 const &color);
};

#endif // !GRAPHICALLETTER_HPP_
