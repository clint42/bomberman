//
// main.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
//
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
//
// Started on  Fri May 16 15:53:47 2014 aurelien prieur
// Last update Fri Jun 13 14:25:18 2014 julie franel
//

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "GameEntities.hpp"
#include "EventsHandler.hpp"
#include "ThreadUI.hpp"
#include "ClientCore.hpp"
#include "SafeQueue.hpp"
#include "AObject.hpp"
#include "Signal.hpp"
#include "MenuHandler.hpp"

//TODO: testing purpose only. Remove it.
extern int debug_align;
int debug_align = 0;

int	main()
{
  srand(time(0));

  ConnexionHandler	connexionHandler;
  Signal		signal(&connexionHandler);
  signal.catchSignal(SIGINT, false);

  //TODO: Move to the right place. Testing purpose only.
  MenuHandler menuHandler(signal);
  t_game	*options;

  if ((options = (menuHandler.launchMenus())) == NULL)
    return (EXIT_FAILURE);
  std::cout << "=========================> " << std::endl;
  std::cout << "MAPNAME= " << options->mapName << std::endl;
  std::cout << "NBPLAYERS= " << options->nbPlayers << std::endl;
  std::cout << "NBBOTS= " << options->nbBots << std::endl;
  std::cout << "TIMEGAME= " << options->timeGame << std::endl;
  std::cout << "IPADDR= " << options->ipAddr << std::endl;
  std::cout << "SERVERPORT= " << options->serverPort << std::endl;
  std::cout << "ISHOST= " << std::boolalpha << options->isHost << std::endl;
  std::cout << "ISDOUBLE= " << std::boolalpha << options->isDouble << std::endl;


  EventsHandler		eventsHandler(connexionHandler);
  GameEntities		gameEntities;
  SafeQueue<std::pair<std::pair<size_t, size_t>, int> >	createInstructs;

  //3: LAUNCH CORE AND GRAPHICENGINE
  ClientCore	core(gameEntities, eventsHandler, createInstructs, connexionHandler);

  if (!core.initialize(options))
    {
      std::cerr << "Initialization failure" << std::endl;
      return (EXIT_FAILURE);
    }

  ThreadUI	threadUI(eventsHandler, gameEntities, createInstructs);
  core.run();

  //TODO: add failure condition to return correct value

  //threadUI.join();
  return (EXIT_SUCCESS);
}
