/*
// Player.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 12:24:05 2014 buret_j
// Last update Sun Jun  8 12:47:46 2014 buret_j
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

static struct { std::string s; Server::Player::Dir d; } g_tab[] = {
  { "UP", Server::Player::UP },
  { "RIGHT", Server::Player::RIGHT },
  { "DOWN", Server::Player::DOWN },
  { "LEFT", Server::Player::LEFT }
};

void
Server::Player::getAction(Server::Player::Action &a, std::string const &s) {
  Dir d = DOWN;
  for (int i = 0; i < 4; ++i)
    if (g_tab[i].s == s) {
      d = g_tab[i].d;
      break ;
    }
  a = d == _orientation ? MOVE : ORIENT;
}
