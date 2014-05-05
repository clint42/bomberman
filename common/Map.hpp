//
// Map.hpp for  in /home/franel_j/tek2/cpp/bomberman/common
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May  5 17:11:21 2014 julie franel
// Last update Mon May  5 18:01:09 2014 julie franel
//

#ifndef		MAP_HPP_
# define	MAP_HPP_

# include	<map>
# include	<utility>
# include	<cstdlib>

class		Map
{
  size_t	_width;
  size_t	_height;
  size_t	_nbPlayers;
  std::string	_key;
  std::map<std::pair<size_t, size_t>, int>	_map;

public:
  Map();
  ~Map();

};

#endif		/* !MAP_HPP */
