//
// Team.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 16:49:49 2014 buret_j
// Last update Tue May  6 17:01:46 2014 buret_j
//

#include "Team.hpp"

Server::Team::Team(size_t id)
  : _id(id), _color(Server::ColorGenerator::make()), _score(0), _players(0) {
}

Server::Team::~Team() {
}
