/*
// Player.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 12:24:05 2014 buret_j
** Last update Mon May 19 17:29:00 2014 lafitt_g
*/

#include "Player.hpp"

Server::Player::Player(size_t id, Server::Team *t, bool bot)
  : _id(id), _bot(bot), _team(t), _posX(0), _posY(0)
    _bombsLimit(1), _bombsOnFloor(0) {
}

Server::Player::~Player() {
}
