#include <openssl/md5.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include "Exception.hpp"
#include "Map.hpp"

/*
** CONSTRUCTOR / DESTRUCTOR
*/

Map::Map(std::string const &filename) : _width(0), _height(0) {
  std::string	name = "./maps/" + filename;
  std::ifstream	file(name.c_str(), std::ios::in);
  std::string	tmp;

  this->_filename = filename;
  std::getline(file, tmp);
  CVRT_STRING_TO_SIZET(tmp, _width);
  std::getline(file, tmp);
  CVRT_STRING_TO_SIZET(tmp, _height);
  std::getline(file, tmp);
  CVRT_STRING_TO_SIZET(tmp, _nbPlayers);
  if (_width < 4 || _height < 4)
    throw MapException("Map size be must equal to 4*4 or higher.");

  this->getMap(_width, _height, file);
  // this->md5It();
  _key = "key"; // THIS IS DEBUG
  file.close();

  if (this->_nbPlayers > ((_width * _height) - (_map.size() - 1)))
    throw MapException("Map is invalid: there is not enough place for players.");
}

Map::Map(const size_t width, const size_t height, const size_t nbPlayers, const std::string &key,
	 const std::map<std::pair<size_t, size_t>, int> &map) {
  this->_width = width;
  this->_height = height;
  this->_nbPlayers = nbPlayers;
  this->_map = map;
  this->_key = key;
}

Map::~Map() {
}


/*
** MEMBER FUNCTIONS
*/

void
Map::getMap(size_t width, size_t height, std::ifstream &file) {
  char				_c;
  size_t			_w = 0;
  size_t			_h = 0;

  while (file.get(_c) // && _h < height
	 )
    {
      std::cout << _c;
      _c -= '0';
      if (!((_c >= 0 && _c <= 2) || _c == ('\n' - '0')))
	throw MapException("Invalid block identifier");
      if (_c == ('\n' - '0'))
	{
	  if (_w < (width - 1))
	    throw MapException("Map size wrong.");
	  _w = 0;
	  _h += 1;
	}
      else if (_c == 1 || _c == 2)
	{
	  if (_w >= width || _h >= height)
	    throw MapException("Map size wrong.");

	  std::pair<size_t, size_t> _pos(_w, _h);
	  _map[_pos] = _c;
	  _w++;
	}
      else
	_w++;
    }
}

void
Map::md5It() {
  std::ifstream filemap((std::string("./maps/") + this->_filename).c_str(), std::ios::in);

  if(filemap) {
    char key[MD5_DIGEST_LENGTH] = {0};
    std::string content, line;

    while (filemap >> line)
      content += line;
    filemap.close();
    MD5((unsigned char *)content.c_str(), content.size(), (unsigned char *)key);
    _key = key;
  } else
    throw Md5Exception();
}

Map::eTypes     Map::generateCase(const size_t x, const size_t y, const size_t width, const size_t height)
{
  if ((y == 0 || y == (height - 1)) ||
      ((y > 0) && (y < (height - 1)) &&
       ((x == 0 || x == (width - 1))))
      )
    return (Map::WALL);
  else if ((x % 2) == 0 && (y % 2) == 0)
    return (Map::WALL);
  else
    {
      size_t nb = rand () % ((width < height) ? height : width);
      return (Map::_mapTypes[nb % 5]);

    }
}

std::vector<Map::eTypes>	Map::_mapTypes;
bool				Map::_isMapInit = false;

void		Map::generateMap(const size_t width, const size_t height,
				 const size_t maxPlayers, const std::string &filename)
{
  size_t	x = 0;
  size_t	y = 0;
  std::ofstream	file;
  std::string	name = "maps/" + filename;

  if (Map::_isMapInit == false)
    {
      Map::_isMapInit = true;
      Map::_mapTypes.push_back(Map::GROUND);
      Map::_mapTypes.push_back(Map::DWALL);
      Map::_mapTypes.push_back(Map::GROUND);
      Map::_mapTypes.push_back(Map::DWALL);
      Map::_mapTypes.push_back(Map::GROUND);
    }
  file.open(name.c_str(), std::ios::out | std::ios::trunc);
  if (file.is_open())
    {
      file << width << std::endl;
      file << height << std::endl;
      file << maxPlayers << std::endl;
      while (y < height)
  	{
  	  x = 0;
  	  while (x < width)
  	    {
  	      file << generateCase(x, y, width, height);
  	      ++x;
  	    }
  	  file << std::endl;
  	  ++y;
  	}
      file.close();
    }
}



/*
** MODIFIERS
*/


void
Map::setElemAtPos(const std::pair<size_t, size_t> &pos, const int &val)
{
  this->_map[pos] = val;
}

int
Map::getElemAtPos(const size_t x, const size_t y) const {
  std::pair<size_t, size_t> p(x, y);
  if (this->_map.find(p) != this->_map.end())
    return (this->_map.find(p)->second);
  return (0);
}

int
Map::getElemAtPos(const std::pair<size_t, size_t> &p) const {
  if (this->_map.find(p) != this->_map.end())
    return (this->_map.find(p)->second);
  return (0);
}

void
Map::deleteElem(const size_t posX, const size_t posY)
{
  std::pair<size_t, size_t>	pos(posX, posY);
  std::map<std::pair<size_t, size_t>, int>::iterator it = this->_map.find(pos);

  if (it != this->_map.end())
    this->_map.erase(it);
}

void
Map::deleteElem(const std::pair<size_t, size_t> pos)
{
  std::map<std::pair<size_t, size_t>, int>::iterator it = this->_map.find(pos);

  if (it != this->_map.end())
    this->_map.erase(it);
}



/*
** EXCEPTION
*/


MapException::MapException(const std::string &msg) throw(): ABombermanException(msg) {}
MapException::~MapException(void) throw() {}

Md5Exception::Md5Exception(void) throw() : ABombermanException("Couldn't open the map") {}
Md5Exception::~Md5Exception(void) throw() {}
