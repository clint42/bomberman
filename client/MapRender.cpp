//
// MapRender.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sun Jun  8 16:08:57 2014 aurelien prieur
// Last update Wed Jun 11 18:45:18 2014 aurelien prieur
//

#include "MapRender.hpp"

MapRender::MapRender(std::string const &mapName): _logicMap(mapName)
{
  _graphEquivalent[Map::GROUND] = VOID;
  _graphEquivalent[Map::WALL] = BLOCK;
  _graphEquivalent[Map::DWALL] = BOX;
  _graphEquivalent[Map::BOMB] = VOID;
  _graphEquivalent[Map::FLAME] = VOID;
  _graphEquivalent[Map::SPEED] = VOID;
}

MapRender::~MapRender()
{
}

bool	MapRender::render(SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &instructQueue)
{
  std::map<std::pair<size_t, size_t>, int> const &map = _logicMap.getMap();

  std::cout << "MAP RENDER" << std::endl;
  for (std::map<std::pair<size_t, size_t>, int>::const_iterator it = map.begin();
       it != map.end();
       ++it)
    {
      instructQueue.push(std::pair<std::pair<size_t, size_t>, int>(it->first,
								   _graphEquivalent[static_cast<Map::eTypes>(it->second)]));
    }
  std::cout << "MAP RENDER END" << std::endl;
  return (true);
}

size_t	MapRender::getWidth(void) const
{
  return (_logicMap.getWidth());
}

size_t	MapRender::getHeight(void) const
{
  return (_logicMap.getHeight());
}

std::string const	&MapRender::getMd5() const
{
  return (_logicMap.getKey());
}
