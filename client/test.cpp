//
// test.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 15:04:13 2014 aurelien prieur
// Last update Mon May 26 13:23:25 2014 aurelien prieur
//

#include <unistd.h>
#include <iostream>
#include "menu/MainMenu.hpp"

int	main()
{
  MainMenu menu;

  menu.initialize();
  menu.build();
  while (menu.update())
    {
      menu.draw();
      menu.timer();
    }
  if (menu.getChoice() >= 0)
    std::cout << "Choice: " << menu.getChoice() << std::endl;
  else
    std::cout << "Exited" << std::endl;
}
