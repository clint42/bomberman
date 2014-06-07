//
// GraphicalText.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 14:08:08 2014 aurelien prieur
// Last update Fri Jun  6 17:26:00 2014 aurelien prieur
//

#ifndef GRAPHICALTEXT_HPP_
# define GRAPHICALTEXT_HPP_

# include <vector>
# include "GraphicalLetter.hpp"

class	GraphicalText
{
  std::vector<GraphicalLetter *>	_text;
  gdl::Texture				_abcTex;
  std::pair<size_t, size_t>		_pos;
  float					_fontSize;
  glm::vec4				_color;

public:
  GraphicalText(std::string const &text, std::pair<size_t, size_t> const &pos,
		glm::vec4 const &color, float const &fontSize,
		std::string const &fontName = "impact");
  ~GraphicalText();
  void	draw(gdl::AShader &shader);
  void	updateColor(glm::vec4 const &color);
  void	updateText(std::string const &text);
};

#endif // !GRAPHICALTEXT_HPP_
