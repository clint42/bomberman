//
// EventsHandler.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu May 29 16:01:34 2014 aurelien prieur
// Last update Fri Jun 13 16:39:00 2014 aurelien prieur
//

#include <iostream>
#include "SdlContext.hh"
#include "EventsHandler.hpp"

EventsHandler::PlayerEvent::PlayerEvent(int player, std::string const &cmd,
					int ks): _player(player), _cmd(cmd), _ks(ks)
{
}

EventsHandler::PlayerEvent::~PlayerEvent()
{
}

int	EventsHandler::PlayerEvent::getPlayer(void) const
{
  return (_player);
}

std::string const	&EventsHandler::PlayerEvent::getCmd(void) const
{
  return (_cmd);
}

bool			EventsHandler::PlayerEvent::hasOccured(keyStatus ks) const
{
  return (_ks & ks);
}

EventsHandler::EventsHandler(ConnexionHandler &connexionHandler): _connexion(connexionHandler), _finished(false)
{
  _lastEvent.insert(std::pair<int, bool>(SDLK_LEFT, false));
  _lastEvent.insert(std::pair<int, bool>(SDLK_RIGHT, false));
  _lastEvent.insert(std::pair<int, bool>(SDLK_UP, false));
  _lastEvent.insert(std::pair<int, bool>(SDLK_SPACE, false));
  _lastEvent.insert(std::pair<int, bool>(SDLK_KP_0, false));
  _lastEvent.insert(std::pair<int, bool>(SDLK_q, false));
  _lastEvent.insert(std::pair<int, bool>(SDLK_d, false));
  _lastEvent.insert(std::pair<int, bool>(SDLK_z, false));
  _lastEvent.insert(std::pair<int, bool>(SDLK_s, false));
  _lastEvent.insert(std::pair<int, bool>(SDLK_p, false));
  _curEvent = _lastEvent;
  _syntaxTab.insert(std::pair<int, PlayerEvent>(SDLK_LEFT,
						EventsHandler::PlayerEvent(1, "MOVE LEFT", DOWN | HOLD | UP)));
  _syntaxTab.insert(std::pair<int, PlayerEvent>(SDLK_RIGHT,
						EventsHandler::PlayerEvent(1, "MOVE RIGHT", DOWN | HOLD | UP)));
  _syntaxTab.insert(std::pair<int, PlayerEvent>(SDLK_UP,
						EventsHandler::PlayerEvent(1, "MOVE UP", DOWN | HOLD | UP)));
  _syntaxTab.insert(std::pair<int, PlayerEvent>(SDLK_DOWN,
						EventsHandler::PlayerEvent(1, "MOVE DOWN", DOWN | HOLD | UP)));
  _syntaxTab.insert(std::pair<int, PlayerEvent>(SDLK_KP_0, EventsHandler::PlayerEvent(1, "BOMB", UP)));
  _syntaxTab.insert(std::pair<int, PlayerEvent>(SDLK_q,
						EventsHandler::PlayerEvent(0, "MOVE LEFT", DOWN | HOLD | UP)));
  _syntaxTab.insert(std::pair<int, PlayerEvent>(SDLK_d,
						EventsHandler::PlayerEvent(0, "MOVE RIGHT", DOWN | HOLD | UP)));
  _syntaxTab.insert(std::pair<int, PlayerEvent>(SDLK_z,
						EventsHandler::PlayerEvent(0, "MOVE UP", DOWN | HOLD | UP)));
  _syntaxTab.insert(std::pair<int, PlayerEvent>(SDLK_s,
						EventsHandler::PlayerEvent(1, "MOVE DOWN", DOWN | HOLD | UP)));
  _syntaxTab.insert(std::pair<int, PlayerEvent>(SDLK_SPACE, EventsHandler::PlayerEvent(1, "BOMB", UP)));
  _syntaxTab.insert(std::pair<int, PlayerEvent>(SDLK_p, EventsHandler::PlayerEvent(-1, "PAUSE", DOWN)));
}

EventsHandler::~EventsHandler()
{
}

EventsHandler::keyStatus	EventsHandler::getInputStatus(int input, bool withoutLock)
{
  EventsHandler::keyStatus	res;

  if (!withoutLock)
    _mutex.lock();
  res = EventsHandler::NONE;
  if (!_lastEvent[input] && _curEvent[input])
    res = EventsHandler::DOWN;
  else if (_lastEvent[input] && !_curEvent[input])
    res = EventsHandler::UP;
  else if (_lastEvent[input] && _curEvent[input])
    res = EventsHandler::HOLD;
  if (!withoutLock)
    _mutex.unlock();
  return (res);
}

bool		EventsHandler::isFinished(void)
{
  bool		res;

  _mutex.lock();
  res = _finished;
  _mutex.unlock();
  return (res);
}

void		EventsHandler::finish(void)
{
  _mutex.lock();
  _finished = true;
  _mutex.unlock();
}

void			EventsHandler::interpret(void)
{
  int			i;

  i = 0;
  for (std::map<int, PlayerEvent>::iterator it = _syntaxTab.begin(); it != _syntaxTab.end(); ++it)
    {
      if (it->second.hasOccured(getInputStatus(it->first, true)))
	{
	  _playerEvents.push_back(&it->second);
	  ++i;
	}
    }
  if (i > 0)
    _connexion.watchEventOnSocket(_connexion.getMasterSocket(), POLLOUT);
}

void			EventsHandler::update(gdl::Input &input)
{
  _mutex.lock();
  _lastEvent = _curEvent;
  for (std::map<int, bool>::iterator it = _curEvent.begin(); it != _curEvent.end(); ++it)
    {
      if (input.getKey(it->first))
	it->second = true;
      else
	it->second = false;
    }
  _mutex.unlock();
}

bool	EventsHandler::cmdToString(std::string &str,
				   int idPlayer1, std::pair<size_t, size_t> const &coord1,
				   int idPlayer2, std::pair<size_t, size_t> const &coord2)
{
  std::ostringstream	oss;

  _mutex.lock();
  for (std::list<PlayerEvent *>::iterator it = _playerEvents.begin(); it != _playerEvents.end(); ++it)
    {
      if ((*it)->getPlayer() == 0)
	{
	  oss << idPlayer1;
	  oss << " " << coord1.first << " " << coord1.second;
	}
      else if (idPlayer1 > 0)
	{
	  oss << idPlayer2;
	  oss << " " << coord2.first << " " << coord2.second;
	}
      oss << " " << (*it)->getCmd() << '\n';
    }
  _playerEvents.clear();
  str = oss.str();
  _mutex.unlock();
  return (true);
}
