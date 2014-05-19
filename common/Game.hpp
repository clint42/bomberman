//
// Game.hpp for  in /home/buret_j/rendu/bomberman/server
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Mon May 12 15:46:31 2014 buret_j
// Last update Mon May 19 17:03:42 2014 buret_j
//

#ifndef GAME_HPP_
# define GAME_HPP_

# define GAME_PLAY_TIME_MULT 5

namespace Game {

  enum	type {
    LAST_MAN_STANDING = 0,
    FREE_FOR_ALL,
    TEAM_DEATH_MATCH
  };

  enum	status {
    // COUNTDOWN = 0,
    // PLAYING,
    // PAUSED,
    // RESULT
  };

  enum	time {
    SHORT = 0,
    MEDIUM,
    LONG
  };

}

#endif /* !GAME_HPP_ */
