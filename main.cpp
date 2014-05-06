//
// main.cpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Tue May  6 11:22:17 2014 julie franel
// Last update Tue May  6 12:08:44 2014 julie franel
//

#include "Exception.hpp"
#include "Map.hpp"

int	main()
{
  try
    {
      Map	*_map = Map::parseMap("test");
      (void)_map;
    }
  catch (MapException e)
    {
      std::cerr << e.message() << std::endl;
    }
  return (0);
}
