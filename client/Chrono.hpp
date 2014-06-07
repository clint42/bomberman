//
// Chrono.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat Jun  7 14:21:33 2014 aurelien prieur
// Last update Sat Jun  7 14:48:03 2014 aurelien prieur
//

#ifndef CHRONO_HPP_
# define CHRONO_HPP_

# include "AObject.hpp"
# include "GraphicalText.hpp"

class	Chrono: public AObject
{
  float		_time;
  GraphicalText	*_text;
  void		buildTimeText(void);

public:
  Chrono();
  virtual ~Chrono();
  virtual bool	initialize(std::pair<size_t, size_t> const &pos = (std::pair<size_t, size_t>(0, 0)));
  virtual bool	update(gdl::Clock const &clock, EventsHandler const &events);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual void	setTime(float const &time);
  virtual float	getTime(void) const;
};

#endif // !CHRONO_HPP_
