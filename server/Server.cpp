/*
// Server.cpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 11:29:52 2014 buret_j
** Last update Tue May  6 15:50:20 2014 lafitt_g
*/

#include "Server.hpp"

Server::Server::Server() {
  this->retrieveConfig();
  this->retrieveMapNames();
}

Server::Server::~Server() {
}

void
Server::Server::retrieveConfig() {
  // it opens `server.cfg' file and collect infos.
}

size_t
Server::Server::retrieveMapNames() {
  // opens `mapcycle.cfg' and fill _mapNames attribute.
  // ?? should it collect game infos specified for each map too ??
}

void
Server::Server::isDead(size_t id)
{
  std::map<size_t, Server::Server::Player *>::iterator it;

  it = this->_playersAlive.find(id);
  this->_playersDead.insert(std::pair<size_t, Server::Server::Player *>(it->first, it->second));
  this->_playersAlive.erase(it);
}

void
Server::Server::allDead()
{
  std::map<size_t, Server::Server::Player *>::iterator it;
  size_t        len;

  len = this->_playersAlive.size();
  while (len > 0)
    {
      it = this->_playersAlive.begin();
      this->_playersDead.insert(std::pair<size_t, Server::Server::Player *>(it->first, it->second));
      this->_playersAlive.erase(it);
      --len;
    }
}

void
Server::Server::putInPlayersAlive()
{
  size_t        maxPlayer;
  size_t        countAlive;
  size_t        countDead;
  std::map<size_t, Server::Server::Player *>::iterator it;

  maxPlayer = this->_map->getNbrSlot();
  countAlive = this->_playersAlive.size();
  countDead = this->_playersDead.size();

  while (countAlive < maxPlayer && countDead > 0)
    {
      it = this->_playersDead.begin();
      this->_playersAlive.insert(std::pair<size_t, Server::Server::Player *>(it->first, it->second));
      this->_playersDead.erase(it);
      ++countAlive;
      --countDead;
    }
}
