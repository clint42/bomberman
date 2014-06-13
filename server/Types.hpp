/*
// Types.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Thu Jun  5 15:57:23 2014 buret_j
// Last update Fri Jun 13 15:17:12 2014 buret_j
*/

#ifndef TYPES_HPP_
# define TYPES_HPP_

# include <string>
# include <vector>

namespace Server {
  struct			t_cmd{
    size_t			id;
    Time			date;
    std::pair<size_t, size_t>	pos;
    std::string			action;
    std::vector<std::string>	params;
    std::string			msg;
  };
}

#endif /* !TYPES_HPP_ */
