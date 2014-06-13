#include "Player.hpp"

Server::Player::Player(size_t id, Socket *s)
  : _id(id), _bot(false), _team(0), _posX(0), _posY(0), _orientation(DOWN),
    _bombsLimit(1), _bombsOnFloor(0), _bombRange(2), _certifiedMd5(false) {
  _socket = s;
}

Server::Player::~Player() {
}

void
Server::Player::updateDateNextCommand(Server::Player::Action a, Time const &date) {
  double mult;
  if (a == MOVE)	 mult = DELAY_MULT_MOVE;
  else if (a == ORIENT)  mult = DELAY_MULT_ORIENT;
  else			 mult = DELAY_MULT_BOMB;

  _dateNextCommand = date - Time(0, 0, 0, (DELAY * mult / _commandTimeMultiplier));
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
  if (this->_orientation == Server::Player::_toDir[param])
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
Server::Player::orient(Dir d)
{
  this->_orientation = d;
  return (true);
}

bool
Server::Player::dropBomb()
{
  this->_bombsOnFloor += 1;
  return (true);
}

void
Server::Player::earnBomb()
{
  this->_bombsLimit += 1;
}

void
Server::Player::earnRange()
{
  this->_bombRange += 1;
}

void
Server::Player::earnSpeed()
{
  this->_commandTimeMultiplier = _commandTimeMultiplier > 0.2 ? _commandTimeMultiplier - 0.1 : _commandTimeMultiplier / 2;
}
