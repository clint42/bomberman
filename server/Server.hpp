/*
// server.hh for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Mon May  5 16:51:35 2014 buret_j
// Last update Thu Jun  5 16:27:42 2014 buret_j
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
# include "Team.hpp"
# include "Types.hpp"
# include "SafeQueue.hpp"
# include "Filter.hpp"
# include "Exception.hpp"
# include "ConnexionHandler.hpp"

namespace Server {
  class	Server {

    bool			_run;

    ConnexionHandler *		_co;
    std::list<Player *>		_peers;
    Game *			_game;

    std::list<t_msg *>		_messages;
    SafeQueue<t_cmd *>		_ext;

    //
    void	getInformation(const std::string &, size_t *, size_t, size_t);
    void	filterCmd();
    void	putCmdInQueue(t_cmd *);
    t_msg	*filterMsg(const t_cmd &);

    //
    // void	isDead(size_t, std::pair<size_t, size_t>);
    // void	allDead();
    // void	putInPlayersAlive();

    Player	*getPlayer(const size_t, const size_t);
    Player	*getPlayer(const size_t id);

    void	movePlayer();
    void	createPlayer();

  public:
    Server(ConnexionHandler *);
    ~Server();

    void	run();
  };

}

#endif /* !SERVER_HPP_ */
