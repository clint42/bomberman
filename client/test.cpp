//
// test.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat May 24 15:04:13 2014 aurelien prieur
// Last update Tue Jun 10 21:36:48 2014 virol_g
//

#include <unistd.h>
#include <iostream>
#include "menu/MainMenu.hpp"
#include "menu/SubMenu.hpp"
#include "menu/CreateMenu.hpp"

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
    {
      t_game	*choice;
      CreateMenu	sub(menu.getContext());
      std::cout << "Choice: " << menu.getChoice() << std::endl;
      sub.initialize();
      sub.build();
      while (sub.update())
	{
	  sub.draw();
	  sub.timer();
	}
      choice = sub.getChoice();
      std::cout << "nb players : " << choice->nbPlayers << std::endl;
      std::cout << "nb bots : " << choice->nbBots << std::endl;
      std::cout << "map : " << choice->mapName << std::endl;
      std::cout << "time game : " << choice->timeGame << std::endl;      
    }
  else
    std::cout << "Exited" << std::endl;
}
