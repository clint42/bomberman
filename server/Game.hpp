#ifndef SERVER__GAME_HPP_
# define SERVER__GAME_HPP_

# define GAME_TIME     5 // (in min)	total time of a map. Must be multiplied by e_time.
# define BOMBTIME      2 // (in sec)
# define COUNTDOWN     5 // (in sec)
# define RESPAWN_DELAY 5 // (in sec)

# include <sstream>

# include "Time.hpp"
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
    typedef enum { SHORT = 1, MEDIUM, LONG } Time_t;
    typedef struct {
      size_t numberOfTeams;  size_t numberOfPlayersPerTeam;
      size_t numberOfRounds; size_t timeOfARound;
      bool roundMustEnd;     size_t playerRespawnDelay;
    } Play;

  private:

    class Bot;

    Map *	_map;
    Play	_params;
    Time_t	_time;
    Messenger *	_messenger;
    Thread *	_bombThread;
    size_t &	_id;

    std::list<Bot *>	_bots;
    Thread *		_botsThread;

    bool	_started;
    Time	_startedAt;
    bool	_paused;
    Time	_pausedAt;
    Time	_endAt;
    bool	_ended;

    size_t	_nbPlayers;
    size_t	_nbBots;

    std::list<Player *> const &	_peers;
    std::map<std::pair<size_t, size_t>, Player *> _players;

    SafeQueue<t_cmd *>		_events;
    CondSafeQueue<t_cmd *>	_bombs;

    Time	_timeLeft;

  public:

    Game(std::string const &m, size_t p, size_t b, size_t t, Type type,
	 std::list<Player *> const &, Messenger *, size_t &);
    ~Game();

    inline Map const *	getMap() const { return _map; }
    inline Play const &	getParams() const { return _params; }
    inline std::string const &getMapName() const { return _map->getFilename(); }
    inline std::string const &getMapMd5() const { return _map->getKey(); }
    inline size_t  getNbrBots() const {return this->_bots.size();}
    inline size_t getNbrPlayers() const {return this->_players.size() - this->_bots.size();}

    void setTimeLeft(size_t time) {
      _startedAt = Time().now();
      _endAt = _startedAt + Time(0, 0, time);
    }
    void updateTimeLeft() { _timeLeft = !_paused ? (_endAt - Time().now()) : (_endAt - _pausedAt); }
    inline Time const &	timeLeft() const { return _timeLeft; }
    inline bool		hasSomethingToDo() const { return !_events.empty(); } // || !_bombs.empty(); }

    void		start();
    inline bool		isStarted() const { return _started; }
    void		pause();
    inline bool		isPaused() const { return _paused; }
    bool		ended() const { return _ended; }
    bool		isEnded() const {
      return _started && !_paused && (!this->timeLeft().inUsec()
				      || _players.size() <= 1
				      || _players.size() == _bots.size());
    }

    inline void		addEvent(t_cmd *c) { _events.push(c); }
    inline void		addBomb(t_cmd *c) { _bombs.push(c); }

    static bool		_isGame;
    static std::map<std::pair<Player::Action, Player::Dir>,
		    bool(Game::*)(Player *, t_cmd *)> func;
    static void *       trampoline_bombsProcessing(void *);
    void		bombsProcessing();

    static void *       trampoline_botsProcessing(void *);
    void		botsProcessing();

    std::pair<size_t, size_t>       generatePos(const size_t posx, const size_t posy);
    size_t		countPeersThatCertified() const;

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
    void		killPlayer(Player *);
    void		killPlayer(const std::pair<size_t, size_t>);

    static std::map<std::string, Game::Type>    _types;
    static bool					_isInit;
    static std::map<int, std::string>		_bonus;

    void		saveGame() const;
    void		loadGame(const std::string &filename);

  private:

    Player *		findPlayerByID(const size_t);
    void		updateBots();
    void		filterCmd(t_cmd *) const;
    bool		process(t_cmd *, Player *);
    void		bombSwitchQueue(t_cmd *, const std::pair<size_t, size_t>);

    void                pickPlayers(size_t);
    void		createBots();

    void		bombExplose(Player *, t_cmd *);
    bool		exploseCase(Player *, const std::pair<size_t, size_t>, t_cmd *);
    void		createBonus(const std::pair<size_t, size_t>, t_cmd *, int);
    void		earnBonus(Player *, int, const std::pair<size_t, size_t>);

    void		buildCmdCreateBomb(t_cmd *, const std::pair<size_t, size_t>);
    inline bool		hasDateNextCommandExpired(Player *p) const {
      // std::cout << "Server::Game::hasDateNextCommandExpired()" << std::endl;
      // std::cout << "dateNextCommand is:" << p->getDateNextCommand() << std::endl;
      // std::cout << "timeLeft is:" << this->timeLeft() << std::endl;
      return p->getDateNextCommand() > this->timeLeft();
    }

    class	Bot {
      Player *	_p;
      Map *	_map;
      std::map<std::pair<size_t, size_t>, Player *>	&_list;

      bool	danger();
      void	attack();
    public:
      Bot(Player *p, Map *m, std::map<std::pair<size_t, size_t>, Player *>  &list);
      ~Bot();

      inline Player *	getPlayer() const { return _p; }
      void		actionBot(const Time &date, SafeQueue<t_cmd *> &events);
    };

  };

}

class           GameException: public ABombermanException
{
public:
  GameException(const std::string &msg) throw();
  virtual ~GameException(void) throw();
};

#endif /* !SERVER__GAME_HPP_ */
