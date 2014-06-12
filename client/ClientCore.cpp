//
// ClientCore.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
//
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
//
// Started on  Thu May 29 15:44:40 2014 aurelien prieur
// Last update Thu Jun 12 11:06:05 2014 aurelien prieur
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
  _configurator(NULL),
  _gameEntities(gameEntities),
  _eventsHandler(eventsHandler),
  _connexion(connexionHandler),
  _createInstructs(createInstructs),
  _map(NULL)
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
  _map->render(_createInstructs);
  _gameEntities.setMapSize(std::pair<size_t, size_t>(_map->getWidth(), _map->getHeight()));
  delete _map;
  return (true);
}

bool			ClientCore::isConfigured(void) const
{
  if (!(_parser->getConfig().idPlayer1 != 0 &&
       (_parser->getConfig().idPlayer2 != 0 || !_gameEntities.isDouble())))
    return (false);
  if (_parser->getConfig().mapName == "")
    return (false);
  if (_configurator->sizeCmd() > 0)
    return (false);
  return (true);
}

bool			ClientCore::initialize(t_game *options)
{
  std::string		string;

  if (connectServer(options) == false)
    return (false);
  _socket = _connexion.getMasterSocket();
  _connexion.watchEventOnSocket(_socket, POLLIN | POLLOUT);
  _configurator = new Configurator(options);
  if (options->isDouble)
    {
      _gameEntities.setDouble();
      _configurator->pushCmd("WITHFRIEND YES\n");
    }
  else
    _configurator->pushCmd("WITHFRIEND NO\n");
  try {
    while (_connexion.update(-1) >= 0 && !isConfigured() && !_configurator->hasErrorOccured())
      {
	if (_map != NULL && _parser->getConfig().idPlayer1 != 0 &&
	    (_parser->getConfig().idPlayer2 != 0 || options->isDouble))
	  {
	    buildMapMd5(string, _parser->getConfig().idPlayer1);
	    _configurator->pushCmd(string);
	    if (options->isDouble)
	      {
		buildMapMd5(string, _parser->getConfig().idPlayer2);
		_configurator->pushCmd(string);
	      }
	  }
	_connexion.perform(&trampolineConfig, this);
      }
    if (_configurator->hasErrorOccured())
      return (false);
  }
  catch (MapException e) {
    std::cerr << "Invalid map: " << e.what() << std::endl;
    delete _configurator;
    return (false);
  }
  delete _configurator;
  return (true);
}

void			ClientCore::buildConfigCmd(std::string &string) const
{
  std::ostringstream	oss;

  oss << _parser->getConfig().idPlayer1 << " 0 0 ";
  oss << "CONFIG " << _configurator->getOptions()->mapName << " ";
  oss << _configurator->getOptions()->nbPlayers << " ";
  oss << _configurator->getOptions()->nbBots << " ";
  oss << _configurator->getOptions()->timeGame << " ";
  oss << "0" << std::endl;
  string = oss.str();
}

void			ClientCore::buildMapMd5(std::string &string, int idPlayer) const
{
  std::ostringstream	oss;
  
  oss << idPlayer << " 0 0 ";
  oss << _map->getMd5() << std::endl;
  string = oss.str();
}

void		ClientCore::config(__attribute__((unused))Socket *socket, bool b[3])
{
  std::string	string;
  
  if (b[2])
    {
      std::cerr << "Connexion reset by host during configuration process" << std::endl;
      _configurator->errorOccured();
    }
  if (b[0])
    {
      _socket->getLine(string);
      std::cout << "[CLIENT] received " << string << std::endl; 
      _parser->run(string);
      if (_parser->getConfig().welcomeReceived)
	{
	  std::cout << "CONFIG push in cmds" << std::endl;
	  buildConfigCmd(string);
	  _configurator->pushCmd(string);
	  _connexion.watchEventOnSocket(_socket, POLLOUT);
	}
      if (_parser->getConfig().mapName != "")
	_map = new MapRender(_parser->getConfig().mapName);
    }
  if (b[1])
    {
      _configurator->popCmd(string);
      std::cout << "[CLIENT] send " << string << std::endl;
      _socket->write(string);
      if (_configurator->sizeCmd() == 0)
	_connexion.unwatchEventOnSocket(_socket, POLLOUT);
    }
}

void	ClientCore::trampolineConfig(void *param, Socket *socket, bool b[3])
{
  reinterpret_cast<ClientCore *>(param)->config(socket, b);
}

void	ClientCore::trampoline(void *param, Socket *socket, bool b[3])
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

 ClientCore::Configurator::Configurator(t_game *options): _error(false), _options(options)
{
}

ClientCore::Configurator::~Configurator()
{
  _cmds.clear();
}

void	ClientCore::Configurator::pushCmd(std::string const &cmd)
{
  _cmds.push_back(cmd);
}

void	ClientCore::Configurator::popCmd(std::string &cmd)
{
  cmd = _cmds[0];
  _cmds.erase(_cmds.begin());
}

bool	ClientCore::Configurator::hasErrorOccured(void) const
{
  return (_error);
}

void	ClientCore::Configurator::errorOccured(void)
{
  _error = true;
}

int	ClientCore::Configurator::sizeCmd(void) const
{
  return (_cmds.size());
}

t_game const	*ClientCore::Configurator::getOptions(void) const
{
  return (_options);
}

