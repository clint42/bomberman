/*
// Player.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 12:24:05 2014 buret_j
// Last update Wed Jun  4 15:07:39 2014 buret_j
*/

#include "Player.hpp"

Server::Player::Player(size_t id, Server::Team *t, bool bot)
  : _id(id), _bot(bot), _team(t), _posX(0), _posY(0), _orientation(UP),
    _bombsLimit(1), _bombsOnFloor(0) {
}

Server::Player::~Player() {
}

size_t
Server::Player::getTimeSinceLastCommand() const {
  timeval t; TIME(t);
  return (t.tv_sec % 1000 * 1000 + t.tv_usec / 1000) -
    (_lastCommand.tv_sec % 1000 * 1000 + _lastCommand.tv_usec / 1000);
}
