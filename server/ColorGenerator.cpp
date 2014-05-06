//
// ColorGenerator.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 15:00:59 2014 buret_j
// Last update Tue May  6 17:59:37 2014 buret_j
//

#include "ColorGenerator.hpp"

size_t
Server::ColorGenerator::make() {
  double hue = rand() + 0.618033988749895;
  hue -= (size_t)hue;

  size_t hueRounded = hue * 6;
  double saturation = 0.5;
  double value = 0.95;
  size_t color;

  double f, p, q, t;
  f = hue * 6 - hueRounded;
  p = value * (1 - saturation);
  q = value * (1 - f * saturation);
  t = value * (1 - (1 - f) * saturation);

  color = hueRounded == 0 || hueRounded == 5 ? value
    : hueRounded == 1 ?				q
    : hueRounded == 2 || hueRounded == 3 ?	p
    :	t;
  color = color * 1000 + (hueRounded == 0 ?			t
			  : hueRounded == 1 || hueRounded == 2 ?	value
			  : hueRounded == 3 ?				q
			  :	p);
  color = color * 1000 + (hueRounded == 0 || hueRounded == 1 ? p
			  : hueRounded == 3 || hueRounded == 4 ?	value
			  : hueRounded == 2 ?				t
			  :	q);
  return (color);
}
