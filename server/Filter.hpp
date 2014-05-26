/*
** Filter.hpp for Filter in /home/lafitt_g/Tek2/c++/bomberman/server
** 
** Made by lafitt_g
** Login   <lafitt_g@lafittg>
** 
** Started on  Fri May 23 14:16:00 2014 lafitt_g
** Last update Mon May 26 15:57:18 2014 lafitt_g
*/

#ifndef FILTER_HPP_
# define FILTER_HPP_

#include <string>
#include <vector>
#include <sstream>

struct				t_cmd
{
  size_t			id;
  std::pair<size_t, size_t>	pos;
  std::string			action;
  std::vector<std::string>	params;
};

class		Filter
{
public:
  Filter(std::string);
  ~Filter();

  void	setCmd(std::string);
  std::string getCmd() const;
  t_cmd *filterCmd();

private:
  std::string	_cmd;
};

#endif /* !FILTER_HPP_ */
