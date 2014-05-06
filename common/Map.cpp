/*
// map.cpp for  in /home/franel_j/tek2/cpp/bomberman/common
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Mon May  5 17:07:18 2014 julie franel
// Last update Tue May  6 18:24:59 2014 julie franel
*/

#include <openssl/md5.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "Exception.hpp"
#include "Map.hpp"

/*
** CONSTRUCTOR / DESTRUCTOR
*/

Map::Map(size_t width, size_t height, size_t nbPlayers, const std::string &key,
	 const std::map<std::pair<size_t, size_t>, int> &map)
{
  this->_width = width;
  this->_height = height;
  this->_nbPlayers = nbPlayers;
  this->_map = map;
  this->_key = key;
}

Map::~Map()
{

}


/*
** MEMBER FUNCTIONS
*/

size_t			Map::getSizeT(const std::string &size)
{
  std::stringstream	ss(size);
  size_t		tmp;

  ss >> tmp;
  return (tmp);
}

void				Map::getMap(size_t &width, size_t &height, std::ifstream &file,
					    std::map<std::pair<size_t, size_t>, int> &_map)
{
  char				_c;
  size_t			_w = 0;
  size_t			_h = 0;
  std::map<char, eTypes>	_types;

  _types['1'] = WALL;
  _types['2'] = DWALL;
  while (file.get(_c))
    {
      if (!((_c >= '0' && _c <= '2') || _c == '\n'))
	throw MapException("Invalid character in map file.\nUsage :\n0 -> \
ground\n1 -> wall\n2 -> destructible wall");
      if (_c == '\n')
	{
	  _w = 0;
	  _h += 1;
	}
      else
	{
	  for (char x = '1'; x <= '2'; ++x)
	    {
	      if (_w >= width)
		throw MapException("Map width is higher than expected.");
	      else if (_h >= height)
		throw MapException("Map height is higher than expected.");
	      std::pair<size_t, size_t> _pos(_w, _h);
	      _map[_pos] = _types[x];
	    }
	  _w++;
	}
    }
}

void
Map::md5It(std::string &save)
{
  std::ifstream filemap(this->_filename.c_str(), std::ios::in);

  if(filemap)
    {
      char key[MD5_DIGEST_LENGTH] = {0};
      std::string content, line;

      while (filemap >> line)
        content += line;
      filemap.close();
      MD5((unsigned char *)content.c_str(), content.size(), (unsigned char *)key);
      save = key;
    }
  else
    throw Md5Exception();
}

Map			*Map::parseMap(const std::string &filename)
{
  std::map<std::pair<size_t, size_t>, int>	_map;
  std::ifstream		file(filename.c_str(), std::ios::in);
  std::string		width;
  std::string		height;
  size_t		_w;
  size_t		_h;
  size_t		_nb;

  std::getline(file, width);
  std::getline(file, height);
  _w = Map::getSizeT(width);
  _h = Map::getSizeT(height);
  if (_w < 4 || _h < 4)
    throw MapException("Map size be must equal to 4*4 or higher.");
  Map::getMap(_w, _h, file, _map);
  file.close();
  _nb = (_w * _h) - (_map.size() - 1);
  if (_nb < 1)
    throw MapException("Map is invalid: there is not enough place for \
players.");
  return (new Map(_w, _h, _nb, "", _map));
}

void		Map::generateMap()
{

}


/*
** GETTERS
*/

size_t                Map::getWidth() const
{
  return (this->_width);
}

size_t                Map::getHeight() const
{
  return (this->_height);
}

size_t                Map::getNbrSlot() const
{
  return (this->_nbPlayers);
}

const std::string     &Map::getKey() const
{
  return (this->_key);
}

const std::map<std::pair<size_t, size_t>, int>        &Map::getMap() const
{
  return (this->_map);
}


/*
** MODIFIERS
*/

void	Map::deleteElem(size_t posX, size_t posY)
{
  std::pair<size_t, size_t>	_pos(posX, posY);
  std::map<std::pair<size_t, size_t>, int>::iterator	it;

  for (it = this->_map.begin(); it != this->_map.end(); ++it)
    {
      if (it->first == _pos)
	{
	  this->_map.erase(it);
	  return ;
	}
    }
}
