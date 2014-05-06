//
// ColorGenerator.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 14:41:04 2014 buret_j
// Last update Tue May  6 15:49:58 2014 buret_j
//

#ifndef COLORGENERATOR_HPP_
# define COLORGENERATOR_HPP_

namespace Server {

  // doc:
  // using HSV (hue, saturation & value)
  // http://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB
  // http://martin.ankerl.com/2009/12/09/how-to-create-random-colors-programmatically/

  class	ColorGenerator {
    // static size_t _count;

    ColorGenerator() {}
    ~ColorGenerator() {}

  public:
    static size_t make();
    // static void   reset();
  };

}

#endif /* !COLORGENERATOR_HPP_ */
