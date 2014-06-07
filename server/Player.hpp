//
// Player.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon May  5 17:14:40 2014 buret_j
// Last update Fri Jun  6 16:01:15 2014 buret_j
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <sys/time.h>
# include <cstdlib>
# include <iostream>

# include "Team.hpp"
# include "Socket.hpp"

# define TIME(t)  gettimeofday(&t, 0)

# define DELAY		   350 // (in msec) default time of all actions.
# define DELAY_MULT_ORIENT 1.0 // multiplier of orientation action time.
# define DELAY_MULT_MOVE   2.0

namespace Server {

  class Player {

  public:

    typedef enum { UP = 0, RIGHT, DOWN, LEFT } Dir;

  private:

    size_t	_id;
    // std::string  _name;
    bool	_bot;
    Team *	_team;
    size_t	_posX, _posY;
    Player::Dir	_orientation;

    size_t	_bombsLimit;
    size_t	_bombsOnFloor;

    timeval	_lastCommand;// date of the action
    double	_lastCommandTimeMultiplier;// differentiating displacement & orientation commands
    double	_commandTimeMultiplier;// used by bonus, '1' by default. ex: 0.5 = speed increased by 2.

    Socket *	_socket;
    

  public:
    Player(size_t, Socket *);
    ~Player();

    inline size_t getID() const { return this->_id; }
    inline Team * getTeam() const { return this->_team; }
    inline bool   isBot() const { return this->_bot; }
    inline size_t getPosX() const { return this->_posX; }
    inline size_t getPosY() const { return this->_posY; }
    
    inline Dir	  getOrientation() const { return this->_orientation; }

    inline void	  setPos(size_t posX, size_t posY) { this->_posX = posX; this->_posY = posY; }
    inline void	  setTeam(Team *t) { this->_team = t; }

    inline void	  poseBomb() { if (_bombsLimit > _bombsOnFloor) _bombsOnFloor += 1; }
    inline void   destroyBomb() { if (_bombsOnFloor > 0) _bombsOnFloor -= 1; }

    inline void   updateDateOfLastCommand() { TIME(_lastCommand); }
    inline double getLastCommandMultiplier() const { return _lastCommandTimeMultiplier; }
    inline double getCommandTimeMultiplier() const { return _commandTimeMultiplier; }
    inline void   setLastCommandMultiplier(double m) { _lastCommandTimeMultiplier = m; }
    inline void   setCommandTimeMultiplier(double m) { _commandTimeMultiplier = m;  }
    size_t	  getTimeSinceLastCommand() const;

    inline Socket *getSocket() const { return _socket; }

  };// ! class Player

}// ! namespace


#endif /* !PLAYER_HPP_ */
