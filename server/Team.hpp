//
// Team.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Tue May  6 14:06:52 2014 buret_j
// Last update Tue May  6 17:02:44 2014 buret_j
//

#ifndef TEAM_HPP_
# define TEAM_HPP_

# include <cstdlib>

# include "ColorGenerator.hpp"

namespace Server {

  class	Team {

    size_t _id;
    size_t _color;
    size_t _score;
    size_t _players;

  public:
    Team(size_t);
    ~Team();

    inline size_t getID() const { return this->_id; }
    inline size_t getColor() const { return this->_color; }
    inline size_t getScore() const { return this->_score; }

    inline void   cleanScore() { this->_score = 0; }
    inline void   incrScore() { this->_score += 1; }
    inline void   decrScore() { this->_score -= 1; }

    inline void   addPlayer() { this->_players += 1; }
    inline void   rmPlayer() { this->_players -= 1; }
    inline size_t getPlayers() const { return this->_players; }

  }; // !class Team

}

#endif /* !TEAM_HPP_ */