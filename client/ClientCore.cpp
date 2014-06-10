//
// ClientCore.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
//
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
//
// Started on  Thu May 29 15:44:40 2014 aurelien prieur
// Last update Tue Jun 10 12:45:52 2014 aurelien prieur
//

#include <iostream>
#include <glm/glm.hpp>
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

bool		ClientCore::initialize()
{
  try {
    MapRender	map("../test.map");
    map.render(_createInstructs);
    _gameEntities.setMapSize(std::pair<size_t, size_t>(map.getWidth(), map.getHeight()));
  }
  catch (MapException e) {
    std::cerr << "Invalid map: " << e.what() << std::endl;
  }
  try {
  _connexion.client(4242, "127.0.0.1");
  //TODO: testing purpose only (remove)
  _connexion.getMasterSocket()->write("CONFIG test.map 1 1 0");
  }
  catch (ConnexionException e) {
    std::cerr << "Connexion refused: " << e.what() << std::endl;
    return (false);
  }
  _socket = _connexion.getMasterSocket();
  _connexion.watchEventOnSocket(_socket, POLLIN);
  _createInstructs.push(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(8, 6), PLAYER + 1));
  _createInstructs.push(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(1, 6), PLAYER + 2));
  _gameEntities.setDouble();
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
