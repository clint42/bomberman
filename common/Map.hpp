/*
// Map.hpp for  in /home/franel_j/tek2/cpp/bomberman/common
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May  5 17:11:21 2014 julie franel
** Last update Tue May  6 17:47:57 2014 lafitt_g
*/

#ifndef			MAP_HPP_
# define		MAP_HPP_

# include		<iostream>
# include		<string>
# include		<map>
# include		<utility>
# include		<cstdlib>

class			Map
{
  size_t		_width;
  size_t		_height;
  size_t		_nbPlayers;
  std::string		_key;
  std::string		_filename;
  std::map<std::pair<size_t, size_t>, int>	_map;

  static size_t		getSizeT(const std::string &size);
  static void		getMap(size_t &width, size_t &height, std::ifstream &file,
			       std::map<std::pair<size_t, size_t>, int> &_map);
  void			md5It(std::string &);

public:
  Map(size_t width, size_t height, size_t nbPlayers, const std::string &filename,
      const std::map<std::pair<size_t, size_t>, int> &_map);
  ~Map();

  size_t		getWidth() const;
  size_t		getHeight() const;
  size_t		getNbrSlot() const;
  const std::string	&getKey() const;
  const std::map<std::pair<size_t, size_t>, int>	&getMap() const;

  static Map		*parseMap(const std::string &filename);
  static void		generateMap();

};

#endif			/* !MAP_HPP */
