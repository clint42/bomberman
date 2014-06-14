/*
// macros.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon Jun  2 13:23:08 2014 buret_j
** Last update Sun Jun 15 00:00:22 2014 lafitt_g
*/

#ifndef MACROS_HPP_
# define MACROS_HPP_

# define CVRT_STRING_TO_SIZET(str, res) { std::stringstream ss(str); ss >> res; }

# define CVRT_SIZET_TO_STRING(strToFill, sizetToAdd) {		\
  std::stringstream ss(strToFill);				\
  ss << sizetToAdd;						\
  strToFill += ss.str();					\
  }

extern int debug_align;
# define DEBUG(str, n) {					\
  /*    std::cout << "[SERVER] ";				\
    for (int i = n < 0; i < debug_align; ++i)			\
      std::cout << " ";						\
    std::cout << str << std::endl;				\
  */    debug_align += n;					\
  }

#endif /* !MACROS_HPP_ */
