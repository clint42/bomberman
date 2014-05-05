//
// server.hh for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Mon May  5 16:51:35 2014 buret_j
// Last update Mon May  5 18:57:05 2014 buret_j
//

#ifndef SERVER_HPP_
# define SERVER_HPP_

# include <list>
# include <map>

# include "Player.hpp"

namespace Server {

  class	Server {
    std::map<std::pair<size_t, size_t>, int>	*entities;
    std::map<size_t, Server::Player *>	playersAlive;// size_t is Player's _id attribute
    std::map<size_t, Server::Player *>	playersDead;
  };

}

#endif /* !SERVER_HPP_ */
