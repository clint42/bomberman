//
// EventsHandler.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu May 29 16:01:34 2014 aurelien prieur
// Last update Mon Jun  2 12:12:58 2014 aurelien prieur
//

#include <iostream>
#include "EventsHandler.hpp"

EventsHandler::EventsHandler(): _current(NULL)
{

}

EventsHandler::~EventsHandler()
{
}

EventsHandler::keyStatus	EventsHandler::getInputStatus(int input)
{
  EventsHandler::keyStatus	res;

  _mutex.lock();
  if (_current == NULL)
    return (NONE);
  res = EventsHandler::NONE;
  if (!_last.getKey(input) && _current->getKey(input))
    res = EventsHandler::DOWN;
  else if (_last.getKey(input) && !_current->getKey(input))
    res = EventsHandler::UP;
  else if (_last.getKey(input) && _current->getKey(input))
    res = EventsHandler::HOLD;
  _mutex.unlock();
  return (res);
}

void		EventsHandler::initialize(gdl::Input *inputs)
{
  _mutex.lock();
  _current = inputs;
  _mutex.unlock();
}

void		EventsHandler::setEvents(gdl::Input last)
{
  _mutex.lock();
  _last = last;
  _mutex.unlock();
}

void		EventsHandler::signal(void)
{
  _condVar.signal();
}

void		EventsHandler::wait(void)
{
  _condVar.wait();
}
