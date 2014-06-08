/*
// Game.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Wed May 28 17:23:30 2014 buret_j
// Last update Mon Jun  9 00:13:09 2014 buret_j
*/

#ifndef SERVER__GAME_HPP_
# define SERVER__GAME_HPP_

# define GAME_TIME     5 // (in min)	total time of a map. Must be multiplied by e_time.
# define RESPAWN_DELAY 5 // (in sec)

# include <sstream>
# include <sys/time.h>

# include "Map.hpp"
# include "Player.hpp"
# include "Thread.hpp"
# include "SafeQueue.hpp"
# include "CondSafeQueue.hpp"
# include "CondVar.hpp"
# include "Types.hpp"
# include "Messenger.hpp"
# include "Exception.hpp"

namespace	Server {

  class	Game {

  public:

    typedef enum { LAST_MAN_STANDING = 0, FREE_FOR_ALL, TEAM_DEATH_MATCH, TEAM_SURVIVOR } Type;
    typedef enum { SHORT = 1, MEDIUM, LONG } Time;
    typedef struct {
      size_t numberOfTeams;  size_t numberOfPlayersPerTeam;
      size_t numberOfRounds; size_t timeOfARound;
      bool roundMustEnd;     size_t playerRespawnDelay;
    } Play;

  private:

    Map *	_map;
    Play	_params;
    Time	_time;
    Messenger *	_messenger;

    bool	_started;
    timeval	_startedAt;
    bool	_paused;
    timeval	_pausedAt;
    timeval	_endAt;

    size_t	_maxPlayers;
    size_t	_maxBots;
    size_t	_round;

    std::map<std::pair<size_t, size_t>, Player *> _players;
    std::list<Team *>		_teams;

    SafeQueue<t_cmd *>		_events;
    CondSafeQueue<t_cmd *>	_bombs;


  public:

    Game(std::string const &m, size_t p, size_t b, size_t t, Type type,
	 std::list<Player *> const &, Messenger *);
    ~Game();

    inline Map const *	getMap() const { return _map; }
    inline Play const &	getParams() const { return _params; }
    size_t		timeLeft() const;
    inline bool		hasSomethingToDo() const { return !_events.empty(); }

    void		start();
    inline bool		isStarted() const { return _started; }
    void		pause();
    inline bool		isPaused() const { return _paused; }
    bool		isEnded() const {
      timeval t;
      gettimeofday(&t, NULL);
      return (_started && !_paused && t.tv_usec > _endAt.tv_usec) ? true : false;
    }

    inline void		addEvent(t_cmd *c) { _events.push(c); }
    inline void		addBomb(t_cmd *c) { _bombs.push(c); }

    bool		moveUp(Player *);
    bool		moveRight(Player *);
    bool		moveDown(Player *);
    bool		moveLeft(Player *);

    bool		orientUp(Player *);
    bool		orientRight(Player *);
    bool		orientDown(Player *);
    bool		orientLeft(Player *);

    void		update();
    void		bombsProcessing();
    void		killPlayer(Player *);

  private:

    void		filterCmd(Server::t_cmd const *, std::string &) const;
    bool		process(Server::t_cmd *, Player *);
    inline bool		hasDateNextCommandExpired(Player *p) const {
      return (p->getDateNextCommand() < this->timeLeft()) ? true : false;
    }
  };

}

#endif /* !SERVER__GAME_HPP_ */
