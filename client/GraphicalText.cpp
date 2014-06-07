//
// GraphicalText.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 14:16:41 2014 aurelien prieur
// Last update Sat Jun  7 17:41:22 2014 aurelien prieur
//

#include <iostream>
#include <stdexcept>
#include "GraphicalText.hpp"

GraphicalText::GraphicalText(std::string const &text, std::pair<size_t, size_t> const &pos,
			     glm::vec4 const &color, float const &fontSize,
			     std::string const &fontName): _pos(pos),
							   _fontSize(fontSize),
							   _color(color)
{
  GraphicalLetter	*letter;

  if (_abcTex.load("./menu/ressources/fonts/" + fontName + ".tga") == false)
    {
      std::cerr << "Couldn load font texture." << std::endl;
      throw std::runtime_error("Failed to load font");
    }
  for (size_t i = 0; i < text.length(); ++i)
    {
      letter = new GraphicalLetter(text[i],
				   std::pair<size_t, size_t>((pos.first + (i * (fontSize - 16))), pos.second),
				   color, fontSize, _abcTex);
      _text.push_back(letter);
    }
}

GraphicalText::~GraphicalText()
{
  for (size_t i = 0; i < _text.size(); ++i)
    delete _text[i];
}

void	GraphicalText::draw(gdl::AShader &shader)
{
  _abcTex.bind();
  for (size_t i = 0; i < _text.size(); ++i)
    _text[i]->draw(shader);
}

void	GraphicalText::updateColor(glm::vec4 const &color)
{
  _color = color;
  for (size_t i = 0; i < _text.size(); ++i)
    _text[i]->updateColor(_color);
}

void	GraphicalText::updateText(std::string const &text)
{
  GraphicalLetter	*letter;

  while (_text.size() > 0)
    {
      delete _text[_text.size() - 1];
      _text.pop_back();
    }
  for (size_t i = 0; i < text.length(); ++i)
    {
      letter = new GraphicalLetter(text[i],
				   std::pair<size_t, size_t>((_pos.first + i * (_fontSize - 16)), _pos.second),
				   _color, _fontSize, _abcTex);
      _text.push_back(letter);
    }
}
