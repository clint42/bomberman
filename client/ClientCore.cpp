//
// ClientCore.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
//
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
//
// Started on  Thu May 29 15:44:40 2014 aurelien prieur
// Last update Sun Jun  8 16:23:02 2014 julie franel
//

#include <iostream>
#include <glm/glm.hpp>
#include "AObject.hpp"
#include "ClientCore.hpp"
#include "EventsHandler.hpp"
#include "Parser.hpp"

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
  _connexion.client(8080, "127.0.0.1");
  }
  catch (ConnexionException e) {
    std::cerr << "Connexion refused: " << e.what() << std::endl;
    return (false);
  }
  _socket = _connexion.getMasterSocket();
  _connexion.watchEventOnSocket(_socket, POLLIN);
  _createInstructs.push(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(0, 0), PLAYER + 1));
  _createInstructs.push(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(4, 1), BOMB));
  _createInstructs.push(std::pair<std::pair<size_t, size_t>, int>(std::pair<size_t, size_t>(1, 1), BLOCK));
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
      if (_gameEntities.getPlayer() == NULL)
	_gameEntities.setPlayer(1);
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
      this->_parser->run(string);
    }
  if (b[1])
    {
      this->_eventsHandler.cmdToString(string, 1, std::pair<size_t, size_t>(0, 0),
				       2, std::pair<size_t, size_t>(0, 0));
      _connexion.getMasterSocket()->write(string);
      _connexion.unwatchEventOnSocket(_connexion.getMasterSocket(), POLLOUT);
    }
}

bool		ClientCore::write(void)
{
  return (false);
}
