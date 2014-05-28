//
// main.cpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Tue May  6 11:22:17 2014 julie franel
// Last update Wed May 28 18:01:32 2014 julie franel
//

#include "Exception.hpp"
#include "Map.hpp"
#include "server/Server.hpp"

int	main()
{
  Server::Server	_server;

  _server.run();
  // try
  //   {
  //     Map	*_map = Map::parseMap("test.map");
  //     std::cout << "BEFORE = " << _map->getMap().size() << std::endl;
  //     _map->deleteElem(2, 3);
  //     std::cout << "AFTER = " << _map->getMap().size() << std::endl;
  //   }
  // catch (MapException e)
  //   {
  //     std::cerr << e.message() << std::endl;
  //   }
  return (0);
}
