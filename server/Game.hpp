#ifndef SERVER__GAME_HPP_
# define SERVER__GAME_HPP_

# define GAME_TIME     5 // (in min)	total time of a map. Must be multiplied by e_time.
# define RESPAWN_DELAY 5 // (in sec)

# include <sstream>
# include <sys/time.h>

# include "Map.hpp"
# include "Team.hpp"
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

    size_t	_nbPlayers;
    size_t	_nbBots;
    size_t	_round;

    std::list<Player *> const &	_peers;
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
    inline std::string const &getMapName() const { return _map->getFilename(); }
    inline std::string const &getMapMd5() const { return _map->getKey(); }

    size_t		timeLeft() const;
    inline bool		hasSomethingToDo() const { return !(_events.empty() || _bombs.empty()); }

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

    static bool		_isGame;
    static std::map<std::pair<Player::Action, Player::Dir>,
		    bool(Game::*)(Player *, t_cmd *)> func;
    static void *       trampoline_bombsProcessing(void *);

    std::pair<size_t, size_t>       generatePos(const size_t posx, const size_t posy);
    size_t		countPeersThatCertified() const;
    void                pickPlayers(size_t);

    bool		moveUp(Player *, t_cmd *);
    bool		moveRight(Player *, t_cmd *);
    bool		moveDown(Player *, t_cmd *);
    bool		moveLeft(Player *, t_cmd *);

    bool		orientUp(Player *, t_cmd *);
    bool		orientRight(Player *, t_cmd *);
    bool		orientDown(Player *, t_cmd *);
    bool		orientLeft(Player *, t_cmd *);

    bool		bombUp(Player *, t_cmd *);
    bool		bombRight(Player *, t_cmd *);
    bool		bombDown(Player *, t_cmd *);
    bool		bombLeft(Player *, t_cmd *);

    void		update();
    void		bombsProcessing();
    void		killPlayer(Player *);
    void		killPlayer(const std::pair<size_t, size_t>);

    static std::map<std::string, Game::Type>    _types;
    static bool                         _isInit;
    static std::map<int, std::string>		_bonus;

  private:

    Player *		findPlayerByID(const size_t);
    void		filterCmd(t_cmd *) const;
    bool		process(t_cmd *, Player *);
    void		bombSwitchQueue(t_cmd *, const std::pair<size_t, size_t>);

    void		bombExplose(Player *, t_cmd *);
    bool		exploseCase(const std::pair<size_t, size_t>, t_cmd *);
    void		createBonus(const std::pair<size_t, size_t>, t_cmd *, int);
    void		earnBonus(Player *, int, const std::pair<size_t, size_t>);

    void		buildCmdCreateBomb(t_cmd *, const std::pair<size_t, size_t>);
    inline bool		hasDateNextCommandExpired(Player *p) const {
      return (p->getDateNextCommand() < this->timeLeft()) ? true : false;
    }
  };

}

class           GameException: public ABombermanException
{
public:
  GameException(const std::string &msg) throw();
  virtual ~GameException(void) throw();
};

#endif /* !SERVER__GAME_HPP_ */
