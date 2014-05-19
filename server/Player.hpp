//
// Player.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon May  5 17:14:40 2014 buret_j
// Last update Mon May 19 16:05:27 2014 buret_j
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <sys/time.h>
# include <cstdlib>

# include "Team.hpp"

# define TIME(t)  gettimeofday(&t, 0)
# define DELAY	  350 // msec

namespace Server {

  class Player {
    size_t	 _id;
    // std::string  _name;
    bool	 _bot;
    Team	*_team;
    size_t	 _posX, _posY;

    size_t	_bombsLimit;
    size_t	_bombsOnFloor;

    timeval	_lastCommand;
    double	_lastCommandTimeMultiplier;// differentiating displacement & orientation commands
    double	_commandTimeMultiplier;// used by bonus, '1' by default

  public:
    Player(size_t, Team *, bool);
    ~Player();

    inline size_t getID() const { return this->_id; }
    inline Team  *getTeam() const { return this->_team; }
    inline bool   isBot() const { return this->_bot; }
    inline size_t getPosX() const { return this->_posX; }
    inline size_t getPosY() const { return this->_posY; }

    inline void	setPos(size_t posX, size_t posY) { this->_posX = posX; this->_posY = posY; }
    inline void setTeam(Team *t) { this->_team = t; }

    inline void	poseBomb() { if (_bombLimit < _bombsOnFloor) _bombsOnFloor += 1; }
    inline void destroyBomb() { if (_bombsOnFloor > 0) _bombOnFloor -= 1; }

    inline void   updateDateOfLastCommand() { TIME(_lastCommand); }
    inline double getLastCommandMultiplier() const { return _lastCommandTimeMultiplier; }
    inline double getCommandTimeMultiplier() const { return _commandTimeMultiplier; }
    inline void   setLastCommandMultiplier(double m) { _lastCommandTimeMultiplier = m; }
    inline void   setCommandTimeMultiplier(double m) { _commandTimeMultiplier = m;  }
    inline size_t getTimeSinceLastCommand() const {
      timeval t; TIME(t);
      return (t.tv_sec % 1000 * 1000 + t.tv_usec / 1000) -
	(_lastCommand.tv_sec % 1000 * 1000 + _lastCommand.tv_usec / 1000);
    }

  };// ! class Player

}// ! namespace


#endif /* !PLAYER_HPP_ */
