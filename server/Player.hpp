//
// Player.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon May  5 17:14:40 2014 buret_j
// Last update Tue May  6 14:15:04 2014 buret_j
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <sys/time.h>

# include "Team.hpp"

# define TIME(t)  gettimeofday(&t, 0)
# define DELAY	  350 // msec

namespace Server {

  class Player {
    size_t	 _id;
    Server::Team *_team;
    bool	 _bot;
    size_t	 _posX, _posY;

    timeval	_lastCommand;
    double	_lastCommandTimeMultiplier;// differentiating displacement & orientation commands
    double	_commandTimeMultiplier;// used by bonus, '1' by default

  public:
    Player();
    ~Player();

    inline bool   isBot() const { return this->_bot; }
    inline size_t getPosX() const { return this->_posX; }
    inline size_t getPosY() const { return this->_posY; }
    inline void   updateDateOfLastCommand() { TIME(_lastCommand); }
    inline size_t getTimeSinceLastCommand() const {
      timeval t; TIME(t);
      return (t.tv_sec % 1000 * 1000 + t.tv_usec / 1000) -
	(_lastCommand.tv_sec % 1000 * 1000 + _lastCommand.tv_usec / 1000);
    }

  };// ! class Player

}// ! namespace


#endif /* !PLAYER_HPP_ */
