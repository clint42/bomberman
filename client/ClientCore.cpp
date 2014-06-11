//
// ClientCore.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
//
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
//
// Started on  Thu May 29 15:44:40 2014 aurelien prieur
// Last update Wed Jun 11 16:07:30 2014 aurelien prieur
//

#include <iostream>
#include <glm/glm.hpp>
#include <unistd.h>
#include "AObject.hpp"
#include "ClientCore.hpp"
#include "EventsHandler.hpp"
#include "Parser.hpp"
#include "MapRender.hpp"

ClientCore::ClientCore(GameEntities &gameEntities, EventsHandler &eventsHandler,
		       SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs,
		       ConnexionHandler &connexionHandler):
  _gameEntities(gameEntities),
  _eventsHandler(eventsHandler),
  _connexion(connexionHandler),
  _createInstructs(createInstructs)
{
  this->_parser = new Parser(this->_gameEntities, this->_createInstructs);
}

ClientCore::~ClientCore()
{
}

bool		ClientCore::connectServer(t_game *options)
{
  bool		continu = true;
  int		tentatives = 0;

  while (continu)
    {
      try {
	_connexion.client(4242, options->ipAddr);
	//TODO: testing purpose only (remove)
	_connexion.getMasterSocket()->write("CONFIG test.map 1 1 0");
	continu = false;
      }
      catch (ConnexionException e) {
	std::cerr << "Connexion refused: " << e.what() << std::endl;
	tentatives += 1;
	if (tentatives == 6)
	  {
	    std::cerr << "Too many connection tentative. Exit." << std::endl;
	    return (false);
	  }
	sleep(1);
      }
    }
  return (true);
}

bool		ClientCore::loadMap(t_game *options)
{
  (void)(options);
  try {
    MapRender	map("test.map");
    map.render(_createInstructs);
    _gameEntities.setMapSize(std::pair<size_t, size_t>(map.getWidth(), map.getHeight()));
  }
  catch (MapException e) {
    std::cerr << "Invalid map: " << e.what() << std::endl;
    return (false);
  }
  return (true);
}

bool		ClientCore::initialize(t_game *options)
{
  if (connectServer(options) == false)
    return (false);
  _socket = _connexion.getMasterSocket();
  _connexion.watchEventOnSocket(_socket, POLLIN);
  _createInstructs.push(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(8, 15), PLAYER + 1));
  _createInstructs.push(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(15, 20), PLAYER + 2));
  //_gameEntities.setDouble();
  // _createInstructs.push(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(4, 1), BOMB));
  // _createInstructs.push(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(1, 1), BLOCK));
  return (true);
}

void	trampoline(void *param, Socket *socket, bool b[3])
{
  reinterpret_cast<ClientCore *>(param)->io(socket, b);
}

bool		ClientCore::run()
{
  //TODO: don't forget to load map
  while (_connexion.update(500) >= 0 && !_eventsHandler.isFinished())
    {
      if (_gameEntities.getPlayer(false, 0) == NULL)
	_gameEntities.setPlayer(1, 0);
      if (_gameEntities.getPlayer(false, 1) == NULL)
	_gameEntities.setPlayer(2, 1);
      _connexion.perform(&trampoline, this);
    }
  return (true);
}

void		ClientCore::io(__attribute__((unused))Socket *socket, bool b[3])
{
  std::string	string;

  if (b[2])
    {
      _eventsHandler.finish();
    }
  if (b[0])
    {
      this->_socket->getLine(string);
      std::cout << string << std::endl;
      this->_parser->run(string);
    }
  if (b[1])
    {
      this->_eventsHandler.cmdToString(string, 1, std::pair<size_t, size_t>(0, 0),
				       2, std::pair<size_t, size_t>(0, 0));
      std::cout << "Sending data: " << string << std::endl;
      _connexion.getMasterSocket()->write(string);
      _connexion.unwatchEventOnSocket(_connexion.getMasterSocket(), POLLOUT);
    }
}

bool		ClientCore::write(void)
{
  return (false);
}
