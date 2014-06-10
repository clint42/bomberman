//
// FpsDisplay.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Tue Jun 10 12:01:10 2014 aurelien prieur
// Last update Tue Jun 10 12:12:09 2014 aurelien prieur
//

#ifndef FPSDISPLAY_HPP_
# define FPSDISPLAY_HPP_

# include "GraphicalText.hpp"

class	FpsDisplay
{
  float		_timer;
  int		_fps;
  GraphicalText	*_text;

public:
  FpsDisplay();
  ~FpsDisplay();
  void	updateTimer(float const &time);
  void	draw(gdl::AShader &shader);
};

#endif // !FPSDISPLAY_HPP_
