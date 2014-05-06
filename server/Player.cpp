//
// Player.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 12:24:05 2014 buret_j
// Last update Tue May  6 17:16:25 2014 buret_j
//

#include "Player.hpp"

Server::Player::Player(size_t id, bool bot)
  : _id(id), _team(0), _bot(bot) {
}

Server::Player::~Player() {
}

