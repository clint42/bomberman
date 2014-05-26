/*
** Filter.hpp for Filter in /home/lafitt_g/Tek2/c++/bomberman/server
** 
** Made by lafitt_g
** Login   <lafitt_g@lafittg>
** 
** Started on  Fri May 23 14:16:00 2014 lafitt_g
** Last update Mon May 26 15:01:30 2014 lafitt_g
*/

#ifndef FILTER_HPP_
# define FILTER_HPP_

#include <string>
#include <vector>

class		FILTER_HPP
{
public:
  Filter(std::string);
  ~Filter();

  void filterCmd();

private:
  std::string	_cmd;
};

struct				t_cmd
{
  size_t			id_player;
  std::pair<size_t, size_t>	pos;
  std::string			action;
  std::vector<std::string>	params;

}

#endif /* !FILTER_HPP_ */
