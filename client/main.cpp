//
// main.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 15:53:47 2014 aurelien prieur
// Last update Fri May 16 18:05:09 2014 aurelien prieur
//

#include <unistd.h>

int	main()
{
  //Launch graphic thread
  GameEntities	gameEntities;
  ThreadUI	threadUI(gameEntities);

  
  //TODO: add failure condition to return correct value
  threadUI.join();
  return (EXIT_SUCCESS)
}
