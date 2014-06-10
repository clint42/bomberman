/*
// Map.hpp for  in /home/franel_j/tek2/cpp/bomberman/common
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May  5 17:11:21 2014 julie franel
// Last update Tue Jun 10 16:11:48 2014 buret_j
*/

#ifndef			MAP_HPP_
# define		MAP_HPP_

# include <iostream>
# include <string>
# include <map>
# include <utility>
# include <cstdlib>

# include "macros.hpp"

class			Map
{
public:
  enum	eTypes
    {
      GROUND,
      WALL,
      DWALL, // Destructible WALL
      BOMB, // bonus
      FLAME, // bonus
      SPEED // bonus
    };

private:
  size_t	_width;
  size_t	_height;
  size_t	_nbPlayers;
  std::string	_key;
  std::string	_filename;
  std::map<std::pair<size_t, size_t>, int>	_map;

  void		getMap(size_t width, size_t height, std::ifstream &file);
  void		md5It();

public:
  Map(std::string const &);
  Map(size_t width, size_t height, size_t nbPlayers, std::string const &filename,
      const std::map<std::pair<size_t, size_t>, int> &_map);
  ~Map();

  inline size_t		getWidth() const { return _width; }
  inline size_t		getHeight() const { return _height; }
  inline size_t		getNbrSlot() const { return _nbPlayers; }
  inline std::string const &	getKey() const { return _key; }
  inline std::map<std::pair<size_t, size_t>, int> const &getMap() const { return _map; }

  int			getElemAtPos(size_t, size_t);
  int			getElemAtPos(std::pair<size_t, size_t> &k) { return _map[k]; }
  void			deleteElem(const size_t posX, const size_t posY);

  static void		generateMap();

};

#endif			/* !MAP_HPP */
