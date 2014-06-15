//
// ScoreManager.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri Jun 13 14:32:18 2014 aurelien prieur
// Last update Sun Jun 15 05:56:40 2014 virol_g
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "ScoreManager.hpp"

ScoreManager::ScoreManager(std::string const &filename): _player1Score(0), _player2Score(0), _filename(filename)
{
  std::ifstream		file;
  std::string		str;
  std::string		subStr;
  int			score;
  size_t		cursor;

  file.open(_filename.c_str());
  if (file.is_open())
    {
      while (file.peek() != EOF)
	{
	  std::getline(file, str);
	  cursor = str.find(' ');
	  subStr = str.substr(0, cursor);
	  std::istringstream	iss(str.substr(cursor));
	  iss >> score;
	  if (subStr == "0")
	    _player1Score.push_back(score);
	  else if (subStr == "1")
	    _player2Score.push_back(score);
	  else
	    {
	      _player1Score.clear();
	      _player2Score.clear();
	      file.close();
	      throw ScoreManagerException("File corrupted");
	    }
	}
      std::sort(_player1Score.begin(), _player1Score.end());
      std::sort(_player2Score.begin(), _player2Score.end());
      std::reverse(_player1Score.begin(), _player1Score.end());
      std::reverse(_player2Score.begin(), _player2Score.end());
      file.close();
    }
}

ScoreManager::~ScoreManager()
{
}

void			ScoreManager::save(void) const
{
  std::ofstream		file;

  file.open(_filename.c_str(), std::ios::out | std::ios::trunc);
  if (file.is_open())
    {
      for (size_t i = 0; i < 10; ++i)
	{
	  if (i < _player1Score.size())
	    file << "0 " << _player1Score[i] << std::endl;
	  if (i < _player2Score.size())
	    file << "1 " << _player2Score[i] << std::endl;
	}
      file.close();
    }
  else
    throw ScoreManagerException("Couldn't open (or create) score file");
}

std::vector<int> const	&ScoreManager::getPlayer1Score(void) const
{
  return (_player1Score);
}

std::vector<int> const	&ScoreManager::getPlayer2Score(void) const
{
  return (_player2Score);
}

void			ScoreManager::addPlayerScore(int score, std::vector<int> &scoreTab)
{
  bool			added = false;

  if (scoreTab.size() > 0)
    {
      for (std::vector<int>::iterator it = scoreTab.begin(); it != scoreTab.end() && !added; ++it)
      	{
      	  if ((*it) < score)
	    {
	      scoreTab.insert(it, score);
	      added = true;
	    }
	}
      if (!added)
	scoreTab.push_back(score);
    }
  else
    scoreTab.push_back(score);
}

void			ScoreManager::addPlayer1Score(int score)
{
  addPlayerScore(score, _player1Score);
}

void			ScoreManager::addPlayer2Score(int score)
{
  addPlayerScore(score, _player2Score);
}

ScoreManagerException::ScoreManagerException(std::string const &what): _what(what)
{
}

ScoreManagerException::~ScoreManagerException() throw()
{
}

const char	*ScoreManagerException::what() const throw()
{
  return (_what.c_str());
}

