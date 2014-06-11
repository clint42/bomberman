//
// GraphicalText.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 14:08:08 2014 aurelien prieur
// Last update Wed Jun 11 10:29:59 2014 aurelien prieur
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
  std::string				_string;

public:
  GraphicalText(std::string const &text, std::pair<size_t, size_t> const &pos,
		glm::vec4 const &color, float const &fontSize,
		std::string const &fontName = "impact");
  ~GraphicalText();
  void	draw(gdl::AShader &shader);
  void	updateColor(glm::vec4 const &color);
  void	updateText(std::string const &text);
  void		addLetter(char c);
  void		delLetter();
  std::string	getString() const;
};

#endif // !GRAPHICALTEXT_HPP_
