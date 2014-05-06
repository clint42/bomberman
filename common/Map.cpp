//
// map.cpp for  in /home/franel_j/tek2/cpp/bomberman/common
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May  5 17:07:18 2014 julie franel
// Last update Tue May  6 11:14:24 2014 julie franel
//

#include <fstream>
#include <sstream>
#include "Exception.hpp"
#include "Map.hpp"

/*
** CONSTRUCTOR / DESTRUCTOR
*/

Map::Map(size_t width, size_t height, size_t nbPlayers, const std::string &key)
{
  this->_width = width;
  this->_height = height;
  this->_nbPlayers = nbPlayers;
  this->_key = key;
}

Map::~Map()
{

}


/*
** MEMBER FUNCTIONS
*/

size_t			Map::getSizeT(const std::string &size) const
{
  std::stringstream	ss(size);
  size_t		tmp;

  ss >> tmp;
  return (tmp);
}

Map		*Map::parseMap(const std::string &filename)
{
  std::ifstream	file(filename.c_str(), std::ios::in);
  std::string	width;
  std::string	height;
  size_t	_w;
  size_t	_h;

  std::getline(file, width);
  std::getline(file, height);
  _w = Map::getSizeT(width);
  _h = Map::getSizeT(height);
  if (_w < 4 || _h < 4)
    throw SizeException();
  return (new Map(_w, _h, 0, ""));
}

void		Map::generateMap()
{

}
