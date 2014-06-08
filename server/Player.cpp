/*
// Player.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 12:24:05 2014 buret_j
** Last update Sun Jun  8 19:55:39 2014 lafitt_g
*/

#include "Player.hpp"

Server::Player::Player(size_t id, Socket *s)
  : _id(id), _bot(false), _team(0), _posX(0), _posY(0), _orientation(DOWN),
    _bombsLimit(1), _bombsOnFloor(0) {
  _socket = s;
}

Server::Player::~Player() {
}

void
Server::Player::updateDateNextCommand(Server::Player::Action a, size_t date) {
  double mult;
  if (a == MOVE)	 mult = DELAY_MULT_MOVE;
  else if (a == ORIENT)  mult = DELAY_MULT_ORIENT;
  else			 mult = DELAY_MULT_BOMB;

  _dateNextCommand = (date - (DELAY * mult / _commandTimeMultiplier) < 0)
    ? 0
    : (date - (DELAY * mult / _commandTimeMultiplier));
}

bool Server::Player::_isInit = false;
std::map<std::string, Server::Player::Dir> Server::Player::_toDir;

void
Server::Player::getAction(Server::Player::Action *a, Server::Player::Dir *dir, const std::string &param)
{
  if (Server::Player::_isInit == false)
    {
      Server::Player::_isInit = true;
      Server::Player::_toDir["UP"] = UP;
      Server::Player::_toDir["RIGHT"] = RIGHT;
      Server::Player::_toDir["DOWN"] = DOWN;
      Server::Player::_toDir["LEFT"] = LEFT;
    }
  if (this->getOrientation() == Server::Player::_toDir[param])
    *a = MOVE;
  else
    *a = ORIENT;
  *dir = Server::Player::_toDir[param];
}

bool
Server::Player::moveUp()
{
  this->_posY -= 1;
  return (true);
}

bool
Server::Player::moveRight()
{
  this->_posX += 1;
  return (true);
}

bool
Server::Player::moveDown()
{
  this->_posY += 1;
  return (true);
}

bool
Server::Player::moveLeft()
{
  this->_posX -= 1;
  return (true);
}

bool
Server::Player::orientUp()
{
  this->_orientation = UP;
  return (true);
}

bool
Server::Player::orientRight()
{
  this->_orientation = RIGHT;
  return (true);
}

bool
Server::Player::orientDown()
{
  this->_orientation = DOWN;
  return (true);
}

bool
Server::Player::orientLeft()
{
  this->_orientation = LEFT;
  return (true);
}
