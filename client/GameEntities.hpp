//
// GameEntities.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 16:54:40 2014 aurelien prieur
// Last update Sun Jun  8 19:01:46 2014 aurelien prieur
//

#ifndef GAMEENTITIES_HPP_
# define GAMEENTITIES_HPP_

# include <pthread.h>
# include <map>
# include <utility>
# include "AObject.hpp"
# include "ThreadException.hpp"
# include "Mutex.hpp"

class	GameEntities
{
  bool							_isDouble;
  AObject						*_player;
  AObject						*_player2;
  int							_playerScore;
  int							_player2Score;
  float							_timeLeft;
  std::pair<size_t, size_t>				_mapSize;
  std::map<std::pair<size_t, size_t>, AObject *>	_entities;
  Mutex							_locker;

public:
  GameEntities();
  ~GameEntities();
  bool		lock();
  bool		unlock();
  bool		addEntity(std::pair<std::pair<size_t, size_t>, int> const &coord);
  bool		deleteEntity(std::pair<size_t, size_t> const &coord);
  AObject	*getEntity(std::pair<size_t, size_t> const &coord);
  std::map<std::pair<size_t, size_t>, AObject *>  &getEntities();
  bool		moveEntity(std::pair<size_t, size_t> const &coord,
			   AObject::EventIn event);
  bool		rotateEntity(std::pair<size_t, size_t> const &coord,
			     AObject::EventIn event);
  void		setPlayer(int id, int nPlayer = 0);
  AObject const	*getPlayer(bool withoutLock = false, int nPlayer = 0);
  void		setPlayerScore(int score, int nPlayer = 0);
  int		getPlayerScore(bool withoutLock = false, int nPlayer = 0);
  void		decreaseTimeLeft(float const &val);
  float		getTimeLeft(void);
  void		setTimeLeft(float const &timeLeft);
  std::pair<size_t, size_t> const	&getMapSize(void);
  void					setMapSize(std::pair<size_t, size_t> const &mapSize);
  bool					isDouble(bool withoutLock = false);
  void					setDouble(void);
};

#endif // !GAMEENTITIES_HPP_
