//
// main.cpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Tue May  6 11:22:17 2014 julie franel
// Last update Tue Jun  3 15:40:50 2014 julie franel
//

#include <cstdlib>
#include <ctime>
#include "Exception.hpp"
#include "Map.hpp"
#include "server/Server.hpp"

int	main()
{
  srand(time(0));
  // ConnexionHandler ch;

  try
    {
      Server::Server	_server;

      _server.run();
    }
  catch (ServerException e)
    {
      std::cerr << e.message() << std::endl;
    }
  catch (MapException e)
    {
      std::cerr << e.message() << std::endl;
    }
  return (0);
}
