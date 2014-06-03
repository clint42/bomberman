//
// main.cpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Tue May  6 11:22:17 2014 julie franel
// Last update Tue Jun  3 10:54:18 2014 buret_j
//

#include <cstdlib>
#include <ctime>
#include "Exception.hpp"
#include "Map.hpp"
#include "server/Server.hpp"

int	main()
{
  srand(time(0));
  ConnexionHandler ch;

  try
    {
      Server::Server	_server(&ch);

      _server.run();
    }
  catch (ServerException e)
    {
      std::cerr << e.message() << std::endl;
    }
  return (0);
}
