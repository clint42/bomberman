//
// macros.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon Jun  2 13:23:08 2014 buret_j
// Last update Thu Jun  5 19:09:20 2014 buret_j
//

#ifndef MACROS_HPP_
# define MACROS_HPP_

# define CVRT_STRING_TO_SIZET(str, res) { std::stringstream ss(str); ss >> res; }

# define CVRT_SIZET_TO_STRING(strToFill, sizetToAdd) {		\
  std::stringstream ss(strToFill);				\
  ss << sizetToAdd;						\
  strToFill += ss.str();					\
  }

#endif /* !MACROS_HPP_ */
