/*
** Filter.hpp for Filter in /home/lafitt_g/Tek2/c++/bomberman/server
** 
** Made by lafitt_g
** Login   <lafitt_g@lafittg>
** 
** Started on  Fri May 23 14:16:00 2014 lafitt_g
** Last update Fri May 30 15:08:42 2014 lafitt_g
*/

#ifndef FILTER_HPP_
# define FILTER_HPP_

#include <string>
#include <vector>
#include <sstream>
#include "Server.hpp"

struct				t_cmd
{
  size_t			id;
  timeval			date;
  std::pair<size_t, size_t>	pos;
  std::string			action;
  std::vector<std::string>	params;
};

struct                      t_msg
{
  timeval                   _date;
  std::string               _msg;
};

class		Filter
{
public:
  Filter(const t_msg &);
  ~Filter();

  void	setCmd(std::string);
  std::string getCmd() const;
  t_cmd *filterCmd();

private:
  t_msg		_msg;
};


#endif /* !FILTER_HPP_ */
