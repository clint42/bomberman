//
// Types.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Thu Jun  5 15:57:23 2014 buret_j
// Last update Sat Jun  7 17:46:33 2014 buret_j
//

#ifndef TYPES_HPP_
# define TYPES_HPP_

# include <string>
# include <vector>

namespace Server {
  struct                          t_cmd{
    size_t                        id;
    size_t                        date;
    std::pair<size_t, size_t>     pos;
    std::string                   action;
    std::vector<std::string>      params;
  };

  struct                      t_msg{
    timeval                   _date;
    std::string               _msg;
  };

}

#endif /* !TYPES_HPP_ */
