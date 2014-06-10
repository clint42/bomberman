//
// GraphicalText.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 14:16:41 2014 aurelien prieur
// Last update Tue Jun 10 14:11:31 2014 aurelien prieur
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
  int			letterPadding;

  letterPadding = (_fontSize / 2) - 10; 
  if (letterPadding < 0)
   letterPadding = 0;
  if (_abcTex.load("./menu/ressources/fonts/" + fontName + ".tga") == false)
    {
      std::cerr << "Couldn't load requested font. " << std::endl;
      if (_abcTex.load("./menu/ressources/fonts/airstrike.tga") == false)
	{
	  throw std::runtime_error("Unable to load default font");
	}
      std::cerr << " Default font (airstrike) set instead." << std::endl;
    }
  for (size_t i = 0; i < text.length(); ++i)
    {
      letter = new GraphicalLetter(text[i],
				   std::pair<size_t, size_t>((pos.first + (i * (fontSize - letterPadding))), pos.second),
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
  int			letterPadding;

  letterPadding = (_fontSize / 2) - 10;
  if (letterPadding < 0)
     letterPadding = 0;
  while (_text.size() > 0)
    {
      delete _text[_text.size() - 1];
      _text.pop_back();
    }
  for (size_t i = 0; i < text.length(); ++i)
    {
      letter = new GraphicalLetter(text[i],
				   std::pair<size_t, size_t>((_pos.first + i * (_fontSize - letterPadding)), _pos.second),
				   _color, _fontSize, _abcTex);
      _text.push_back(letter);
    }
}
