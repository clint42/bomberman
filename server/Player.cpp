/*
// Player.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 12:24:05 2014 buret_j
<<<<<<< HEAD
** Last update Mon May 12 17:21:44 2014 lafitt_g
*/
=======
// Last update Mon May 19 16:05:19 2014 buret_j
//
>>>>>>> f4b50b9ff128faccc9605a143891dac29c816bb1

#include "Player.hpp"

Server::Player::Player(size_t id, Server::Team *t, bool bot)
  : _id(id), _bot(bot), _team(t), _posX(0), _posY(0)
    _bombsLimit(1), _bombsOnFloor(0) {
}

Server::Player::~Player() {
}
