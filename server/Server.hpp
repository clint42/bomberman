//
// server.hh for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Mon May  5 16:51:35 2014 buret_j
** Last update Tue May  6 15:44:41 2014 lafitt_g
//

#ifndef SERVER_HPP_
# define SERVER_HPP_

# include <list>
# include <map>

# include "Player.hpp"
# include "Map.hpp"
# include "Exception.hpp"

namespace Server {

  class	Server {
    std::list<Server::Team *> _teams;
    std::map<size_t, Server::Player *>	_playersAlive;// size_t is Player's _id attribute
    std::map<size_t, Server::Player *>	_playersDead;

    Map				*_map;
    std::list<std::string>	_mapNames;

    void	retrieveConfig();
    size_t	retrieveMapNames();
    void	isDead(size_t);
    void	allDead();
    void	putInPlayersAlive();

  public:
    Server();
    ~Server();

  };

}

#endif /* !SERVER_HPP_ */
