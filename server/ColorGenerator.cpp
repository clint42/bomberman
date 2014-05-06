//
// ColorGenerator.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 15:00:59 2014 buret_j
// Last update Tue May  6 16:11:27 2014 buret_j
//

#include "ColorGenerator.hpp"

static unsigned char
(hsvToRGBTab[3])(double hue, double saturation, double value) {
  unsigned char rgb[3];
  size_t hueRounded = hue * 6;

  double f, p, q, t;
  f = hue * 6 - hueRounded;
  p = value * (1 - saturation);
  q = value * (1 - f * saturation);
  t = value *  (1 - (1 - f) * saturation);

  rgb[0] = hueRounded == 0 || hueRounded == 5 ? value
    : hueRounded == 1 ?				q
    : hueRounded == 2 || hueRounded == 3 ?	p
    :	t;
  rgb[1] = hueRounded == 0 ?			t
    : hueRounded == 1 || hueRounded == 2 ?	value
    : hueRounded == 3 ?				q
    :	p;
  rgb[2] = hueRounded == 0 || hueRounded == 1 ? p
    : hueRounded == 3 || hueRounded == 4 ?	value
    : hueRounded == 2 ?				t
    :	q;
}

static size_t
convertRGBTabToRGB(unsigned char tab[3]) {
}

size_t
Server::ColorGenerator::make() {
  double goldenRatio = 0.618033988749895;
  
}

// void
// Server::ColorGenerator::reset() {
//   Server::ColorGenerator::_goldenRatioMultiple = 0;
// }
