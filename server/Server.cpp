//
// Server.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 11:29:52 2014 buret_j
// Last update Tue May  6 11:53:06 2014 buret_j
//

#include "Server.hpp"

Server::Server() {
  this->retrieveConfig();
  this->retrieveMapNames();
}

Server::~Server() {
}

void
Server::retrieveConfig() {
  // it opens `server.cfg' file and collect infos.
}

size_t
Server::retrieveMapNames() {
  // opens `mapcycle.cfg' and fill _mapNames attribute.
  // ?? should it collect game infos specified for each map too ??
}
