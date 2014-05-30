//
// Game.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Wed May 28 17:23:30 2014 buret_j
// Last update Thu May 29 16:46:16 2014 buret_j
//

#ifndef SERVER__GAME_HPP_
# define SERVER__GAME_HPP_

# define GAME_TIME     5 // (in min)	total time of a map. Must be multiplied by e_time.
# define RESPAWN_DELAY 5 // (in sec)

namespace	Server {

  class	Game {

  public:

    enum { LAST_MAN_STANDING = 0, FREE_FOR_ALL, TEAM_DEATH_MATCH, TEAM_SURVIVOR } Type;
    enum { SHORT = 1, MEDIUM, LONG } Time;
    typedef struct {
      size_t numberOfTeams;  size_t numberOfPlayersPerTeam;
      size_t numberOfRounds; size_t timeOfARound;
      bool roundMustEnd;     size_t playerRespawnDelay;
    } Play;

    // const Server::Game::Play g_Plays[] = {
    //   { 0,  1, 1, 0, false, 0 },
    //   { 0,  1, 1, 0, false, RESPAWN_DELAY },
    //   { 4, 16, 1, 0, false, RESPAWN_DELAY },
    //   { 4, 16, 0, 2,  true, 0 }
    // };

    Game(); // params: mapname, playersCount, botCount, time...
    ~Game();

  };

}

#endif /* !SERVER__GAME_HPP_ */
