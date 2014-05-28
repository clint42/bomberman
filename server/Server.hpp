/*
// server.hh for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Mon May  5 16:51:35 2014 buret_j
// Last update Wed May 28 18:06:39 2014 julie franel
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

    SafeQueue<t_cmd *>		_events;
    SafeQueue<t_cmd *>		_bomb;

    struct			t_msg
    {
      timeval			_date;
      std::string		_msg;
    };
    std::list<t_msg *>		_messages;

    ScopedLock			_eventMutex;
    ScopedLock			_bombMutex;

    size_t	retrieveMapNames();
    void	setTime();

    //
    void	isDead(size_t, std::pair<size_t, size_t>);
    void	allDead();
    void	putInPlayersAlive();

    Player	*getPlayer(size_t, size_t);
    Player	*getPlayer(size_t id);

  public:
    Server();
    ~Server();

    void	run();
  };

}

#endif /* !SERVER_HPP_ */
