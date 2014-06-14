//
// EventsHandler.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu May 29 15:57:53 2014 aurelien prieur
// Last update Sun Jun 15 01:06:37 2014 aurelien prieur
//

#ifndef EVENTSHANDLER_HPP_
# define EVENTSHANDLER_HPP_

# include <Input.hh>
# include <vector>
# include <utility>
# include <map>
# include <sstream>
# include <string>
# include "ConnexionHandler.hpp"
# include "Mutex.hpp"
# include "CondVar.hpp"

class		EventsHandler
{
public:
  enum	keyStatus
    {
      DOWN = 1,
      HOLD = 2,
      UP = 4,
      NONE = 8
    };
private:
  class		PlayerEvent
  {
    int		_player;
    std::string	_cmd;
    int		_ks;
  public:
    PlayerEvent(int player, std::string const &cmd, int ks);
    ~PlayerEvent();
    int		getPlayer(void) const;
    std::string	const &getCmd(void) const;
    bool	hasOccured(keyStatus ks) const;
  };
  std::map<int, PlayerEvent>	_syntaxTab;
  std::map<int, bool>		_lastEvent;
  std::map<int, bool>		_curEvent;
  std::list<PlayerEvent *>	_playerEvents;
  ConnexionHandler		&_connexion;
  Mutex				_mutex;
  bool				_finished;
  bool				_endGame;

public:
  EventsHandler(ConnexionHandler &connexionHandler);
  ~EventsHandler();
  keyStatus		getInputStatus(int input, bool withoutLock = false);
  void			initialize(gdl::Input *inputs);
  void			update(gdl::Input &input);
  void			interpret(void);
  bool			isFinished(void);
  void			finish(void);
  bool			cmdToString(std::string &str,
				     int idPlayer1, std::pair<size_t, size_t> const &coord1,
				     int idPlayer2 = -1,
				     std::pair<size_t, size_t> const &coord2 = (std::pair<size_t, size_t>(0, 0)));
  void			endGame(void);
  void			isEndGame(void) const;
};

#endif // !EVENTHANDLER_HPP_
