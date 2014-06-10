/*
// server.hh for  in /home/buret_j/rendu/bomberman
//
// Made by buret_j
// Login   <buret_j@epitech.net>
//
// Started on  Mon May  5 16:51:35 2014 buret_j
// Last update Tue Jun 10 17:21:47 2014 buret_j
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

    std::list<std::string *>	_messages;
    std::list<t_cmd *>		_ext;

    void	getInformation(const std::string *, size_t *, size_t, size_t);
    void	filterMsg(); // pop t_msg => t_cmd; calls putCmdInQueue()
    void	putCmdInQueue(t_cmd *);

    inline size_t countPeers() const { return _peers.size(); }


    bool	funcWelcome(const t_cmd *);
    bool	funcPause(const t_cmd *);
    bool	funcKill(const t_cmd *);

    void	watchEvent(int e);
    void	unwatchEvent(int e);

  public:
    Server(ConnexionHandler *);
    ~Server();

    void	run();
    void	addPeer(Socket *);
    void	peerDisconnected(Socket *);
    void        readMessage(Socket *);
    void	sendMessage(Socket *);
    bool	manageAdminCommand();

    static std::map<std::string, bool (Server::Server::*)(const t_cmd *)>	_func;
    static bool									_isInit;
    static void	trampoline_performResult(void *p, Socket *, bool b[3]);
  };

}

#endif /* !SERVER_HPP_ */
