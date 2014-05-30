/*
// Map.hpp for  in /home/franel_j/tek2/cpp/bomberman/common
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May  5 17:11:21 2014 julie franel
// Last update Fri May 30 16:59:07 2014 julie franel
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
  size_t		_width;
  size_t		_height;
  size_t		_nbPlayers;
  std::string		_key;
  std::string		_filename;
  std::map<std::pair<size_t, size_t>, int>	_map;

  static size_t		getSizeT(const std::string &size);
  static void		getMap(const size_t width, const size_t height, std::ifstream &file,
			       std::map<std::pair<size_t, size_t>, int> &_map);

  void			md5It(std::string &);

public:
  Map(const size_t width, const size_t height, const size_t nbPlayers, const std::string &filename,
      const std::map<std::pair<size_t, size_t>, int> &_map);
  ~Map();

  const size_t		&getWidth() const;
  const size_t		&getHeight() const;
  const size_t		&getNbrSlot() const;
  const std::string	&getKey() const;
  const std::map<std::pair<size_t, size_t>, int>	&getMap() const;

  void			deleteElem(const size_t posX, const size_t posY);

  static Map		*parseMap(const std::string &filename);
  static void		generateMap();

};

#endif			/* !MAP_HPP */
