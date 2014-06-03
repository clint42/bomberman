/*
** Filter.hpp for Filter in /home/lafitt_g/Tek2/c++/bomberman
** 
** Made by lafitt_g
** Login   <lafitt_g@lafittg>
** 
** Started on  Mon Jun  2 18:21:37 2014 lafitt_g
** Last update Mon Jun  2 18:54:49 2014 lafitt_g
*/

#ifndef FILTER_HPP_
# define FILTER_HPP_

#include <sstream>
#include <string>
#include <vector>

struct				t_cmd
{
  size_t			id;
  timeval			date;
  std::pair<size_t, size_t>	pos;
  std::string			action;
  std::vector<std::string>	params;
};

struct			t_msg
{
  timeval		_date;
  std::string		_msg;
};

void		getInformation(const std::string &, size_t *, size_t, size_t);
t_cmd		*filterCmd(const t_msg &);

#endif /* !FILTER_HPP_ */
