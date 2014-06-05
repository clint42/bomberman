/*
// server.hh for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Mon May  5 16:51:35 2014 buret_j
** Last update Thu Jun  5 12:02:17 2014 lafitt_g
*/

#ifndef SERVER_HPP_
# define SERVER_HPP_

# include <list>
# include <vector>
# include <map>
# include <sstream>
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

  struct                          t_cmd{
    size_t                        id;
    timeval                       date;
    std::pair<size_t, size_t>     pos;
    std::string                   action;
    std::vector<std::string>      params;
  };

  struct                      t_msg{
    timeval                   _date;
    std::string               _msg;
  };


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
    SafeQueue<t_cmd *>		_ext;

    // ConnexionHandler test;

    std::list<t_msg *>		_messages;

    size_t	retrieveMapNames();
    void	setTime();

    //
    void	getInformation(const std::string &, size_t *, size_t, size_t);
    void	filterCmd(const t_msg &);
    void	putCmdInQueue(t_cmd *);
    t_msg	*filterMsg(const t_cmd &);

    //
    void	isDead(size_t, std::pair<size_t, size_t>);
    void	allDead();
    void	putInPlayersAlive();

    Player	*getPlayer(const size_t, const size_t);
    Player	*getPlayer(const size_t id);

    void	movePlayer();
    void	createPlayer();

  public:
    Server();
    ~Server();

    void	run();
  };

}

#endif /* !SERVER_HPP_ */
