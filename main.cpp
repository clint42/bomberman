//
// main.cpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Tue May  6 11:22:17 2014 julie franel
// Last update Wed May 21 17:06:37 2014 julie franel
//

#include "server/SocketSrv.hpp"
#include "Exception.hpp"
#include "Map.hpp"

int	main()
{
  SocketSrv	*socket = new SocketSrv(4242, SocketSrv::CLIENT);
  (void)socket;
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
