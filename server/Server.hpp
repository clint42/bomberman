/*
// server.hh for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Mon May  5 16:51:35 2014 buret_j
// Last update Fri May 30 17:38:01 2014 julie franel
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
# include "SafeQueue.hpp"
# include "Filter.hpp"
# include "Exception.hpp"
// # include "ConnexionHandler.hpp"

namespace Server {

  class	Server {
    std::map<std::pair<size_t, size_t>, Player *> _playersAlive;
    std::map<std::pair<size_t, size_t>, Player *> _playersDead;
    std::list<Team *>	_teams;

    std::list<std::string>	_mapNames;
    Map *			_map;
    // Game::Type		_gameType;
    // Game::Time		_gameTimeMult;
    timeval			_dateEnd;

    SafeQueue<t_cmd *>		_events;
    SafeQueue<t_cmd *>		_bomb;
    SafeQueue<t_cmd *>		_cmd;

    // ConnexionHandler test;

    std::list<t_msg *>		_messages;

    size_t	retrieveMapNames();
    void	setTime();

    //
    void	isDead(size_t, std::pair<size_t, size_t>);
    void	allDead();
    void	putInPlayersAlive();

  public:
    Server();
    ~Server();

  };

}

#endif /* !SERVER_HPP_ */
