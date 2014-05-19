/*
// server.hh for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Mon May  5 16:51:35 2014 buret_j
// Last update Tue May 13 14:00:46 2014 buret_j
*/

#ifndef SERVER_HPP_
# define SERVER_HPP_

# include <list>
# include <map>
# include <cstdlib>

# include "Game.hpp"
# include "Player.hpp"
# include "Map.hpp"
# include "Team.hpp"
# include "Exception.hpp"

namespace Server {

  class	Server {
    std::map<std::pair<size_t, size_t>, Player *> _playersAlive;
    std::map<std::pair<size_t, size_t>, Player *> _playersDead;
    std::list<Team *>	_teams;

    std::list<std::string>	_mapNames;
    Map *			_map;
    Game::type			_gameType;
    Game::time			_gameTimeMult;
    timeval			_dateEnd;

    size_t	retrieveMapNames();
    void	setTime();

    //
    void	isDead(size_t);
    void	allDead();
    void	putInPlayersAlive();

  public:
    Server();
    ~Server();

  };

}

#endif /* !SERVER_HPP_ */
