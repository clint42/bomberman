//
// map.cpp for  in /home/franel_j/tek2/cpp/bomberman/common
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May  5 17:07:18 2014 julie franel
// Last update Mon May  5 19:40:54 2014 julie franel
//

#include <fstream>
#include "Map.hpp"

/*
** CONSTRUCTOR / DESTRUCTOR
*/

Map::Map(const std::string &filename)
{
  this->parseMap(filename);
  this->_width = 0;
  this->_height = 0;
  this->_nbPlayers = 0;
  this->_key = "";
}

Map::Map()
{
  this->generateMap();
}

Map::~Map()
{

}


/*
** MEMBER FUNCTIONS
*/

void		Map::parseMap(const std::string &filename)
{
  std::ifstream	file(filename.c_str(), std::ios::in);
  std::string	name;

  std::getline(file, name);
  std::cout << "1ST LINE = " << name << std::endl;
}

void		Map::generateMap()
{

}
