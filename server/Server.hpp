/*
// server.hh for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Mon May  5 16:51:35 2014 buret_j
// Last update Fri Jun  6 17:52:07 2014 buret_j
*/

#ifndef SERVER_HPP_
# define SERVER_HPP_

# include <list>
# include <vector>
# include <map>
# include <sstream>
# include <cstdlib>
# include "macros.hpp"

# include "Game.hpp"
# include "Player.hpp"
# include "Team.hpp"
# include "Types.hpp"
# include "SafeQueue.hpp"
# include "Filter.hpp"
# include "Exception.hpp"
# include "ConnexionHandler.hpp"
# include "Messenger.hpp"

namespace Server {
  class	Server {

    bool			_run;

    ConnexionHandler *		_co;
    Messenger			_messenger;
    std::list<Player *>		_peers;
    Game *			_game;

    std::list<t_msg *>		_messages;
    SafeQueue<t_cmd *>		_ext;

    //
    void	getInformation(const std::string &, size_t *, size_t, size_t);
    void	filterCmd(); // pop t_msg => t_cmd; calls putCmdInQueue()
    void	putCmdInQueue(t_cmd *);

    //
    // void	isDead(size_t, std::pair<size_t, size_t>);
    // void	allDead();
    // void	putInPlayersAlive();

    inline size_t countPeers() const { return _peers.size(); }

  public:
    Server(ConnexionHandler *);
    ~Server();

    void	run();
    void	addPeer(Socket *);
    void	addMessage(Socket *);
    void	sendMessage(Socket *);
  };

}

#endif /* !SERVER_HPP_ */
