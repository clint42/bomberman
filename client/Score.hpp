//
// Score.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Tue Jun 10 18:19:10 2014 aurelien prieur
// Last update Tue Jun 10 19:04:58 2014 aurelien prieur
//

#ifndef SCORE_HPP_
# define SCORE_HPP_

# include "GraphicalText.hpp"

class	Score
{
  bool		_isPlayer2;
  int		_score;
  GraphicalText	*_text;
  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
  bool		loadTexture(void);

public:
  Score(bool isPlayer2 = false);
  ~Score();
  bool	initialize(void);
  void	update(int score);
  void	draw(gdl::AShader &shader);
  int	getScore(void) const;
};

#endif // !SCORE_HPP_
