//
// MapRender.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sun Jun  8 16:00:59 2014 aurelien prieur
// Last update Sun Jun  8 18:26:07 2014 aurelien prieur
//

#ifndef MAPRENDER_HPP_
# define MAPRENDER_HPP_

# include <map>
# include "Map.hpp"
# include "AObject.hpp"
# include "SafeQueue.hpp"

class	MapRender
{
  std::map<Map::eTypes, ObjectType>	_graphEquivalent;
  Map					_logicMap;

public:
  MapRender(std::string const &mapName);
  ~MapRender();
  bool	render(SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &instructQueue);
  size_t	getWidth(void) const;
  size_t	getHeight(void) const;
};

#endif // !MAPRENDER_HPP_
