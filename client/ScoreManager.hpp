//
// ScoreManager.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri Jun 13 14:20:38 2014 aurelien prieur
// Last update Fri Jun 13 15:20:52 2014 aurelien prieur
//

#ifndef SCOREMANAGER_HPP_
# define SCOREMANAGER_HPP_

#include <vector>
#include <string>
#include <exception>

class	ScoreManager
{
  std::vector<int>	_player1Score;
  std::vector<int>	_player2Score;
  std::string const	&_filename;
  void			sort(void);
  void			addPlayerScore(int score, std::vector<int> &scoreTab);
public:
  ScoreManager(std::string const &filename);
  ~ScoreManager();
  void				save(void) const;
  std::vector<int> const	&getPlayer1Score(void) const;
  std::vector<int> const	&getPlayer2Score(void) const;
  void				addPlayer1Score(int score);
  void				addPlayer2Score(int score);
};

class	ScoreManagerException: std::exception
{
  std::string	const _what;
public:
  ScoreManagerException(std::string const &what);
  ~ScoreManagerException() throw();
  const char	*what() const throw();
};

#endif // !SCOREMANAGER_HPP_
