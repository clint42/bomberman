//
// Player.hpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman_ex
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 13:07:42 2014 aurelien prieur
// Last update Mon Jun  9 10:45:55 2014 aurelien prieur
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include "AObject.hpp"
# include "EventsHandler.hpp"

class	Player: public AObject
{
  gdl::Model	_model;
  float		_speed;
  bool		_toDraw;
  bool		_mainAnimStarted;
  void		setAnim(EventsHandler const &events);
  float		genColorComponent(void) const;

public:
  Player(int id);
  virtual ~Player();
  virtual bool	initialize(std::pair<size_t, size_t> const &pos = (std::pair<size_t, size_t>(0, 0)));
  virtual void	updateMovement(void);
  virtual bool	update(gdl::Clock const &clock, EventsHandler const &events);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif // !PLAYER_HPP_