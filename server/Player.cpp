/*
// Player.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 12:24:05 2014 buret_j
** Last update Mon May 12 17:21:44 2014 lafitt_g
*/

#include "Player.hpp"

Server::Player::Player(size_t id, bool bot)
  : _id(id), _team(0), _bot(bot) {
}

Server::Player::~Player() {
}
