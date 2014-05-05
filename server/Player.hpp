//
// Player.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon May  5 17:14:40 2014 buret_j
// Last update Mon May  5 18:47:58 2014 buret_j
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <sys/time.h>

# define TIME(t)	gettimeofday(&t, 0)

namespace Server {

  class Player {
    size_t	_id;
    bool	_bot;
    size_t	_posX, _posY;
    timeval	_lastCommand;

  public:
    inline bool   isBot() const { return this->_bot; }
    inline size_t getPosX() const { return this->_posX; }
    inline size_t getPosY() const { return this->_posY; }
    inline size_t getTimeSinceLastCommand() { timeval t; TIME(t); return t.tv_sec-_lastCommand.tv_sec; }
    inline void   updateDateOfLastCommand() { TIME(_lastCommand); }

  };// ! class Player

}// ! namespace


#endif /* !PLAYER_HPP_ */
