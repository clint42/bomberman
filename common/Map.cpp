#include <openssl/md5.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "Exception.hpp"
#include "Map.hpp"

/*
** CONSTRUCTOR / DESTRUCTOR
*/

Map::Map(std::string const &filename) {
  std::ifstream	file(filename.c_str(), std::ios::in);
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

  while (file.get(_c))
    {
      _c -= '0';
      if (!(_c >= 0 || _c <= 2 || _c == ('\n' - '0')))
	throw MapException("Invalid block identifier");
      if (_c == ('\n' - '0'))
	{
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
  std::ifstream filemap(this->_filename.c_str(), std::ios::in);

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

void
Map::generateMap() {

}



/*
** MODIFIERS
*/


void	Map::setElemAtPos(const std::pair<size_t, size_t> &pos, const int &val)
{
  this->_map[pos] = val;
}

int
Map::getElemAtPos(size_t x, size_t y) {
  std::pair<size_t, size_t> p(x, y);
  if (_map[p])
    return _map[p];
  return (0);
}

int
Map::getElemAtPos(const std::pair<size_t, size_t> &p) {
  if (_map[p])
    return _map[p];
  return (0);
}

void	Map::deleteElem(const size_t posX, const size_t posY)
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
