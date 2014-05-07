//
// Player.cpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Wed May  7 12:13:28 2014 julie franel
// Last update Wed May  7 14:14:35 2014 julie franel
//

#include "Player.hpp"

/*
** CONSTRUCTOR / DESTRUCTOR
*/

Client::Player::Player(const size_t &id, const size_t &posX, const size_t &posY,
		       const size_t &color, const std::string &name)
{
  this->_id = id;
  this->_posX = posX;
  this->_posY = posY;
  this->_color = color;
  this->_name = name;
}

Client::Player::~Player()
{

}


/*
** MEMBER FUNCTIONS
*/

size_t              Client::Player::getId() const
{
  return (this->_id);
}

size_t              Client::Player::getPosX() const
{
  return (this->_posX);
}

size_t              Client::Player::getPosY() const
{
  return (this->_posY);
}

size_t              Client::Player::getColor() const
{
  return (this->_color);
}

const std::string   &Client::Player::getName() const
{
  return (this->_name);
}
