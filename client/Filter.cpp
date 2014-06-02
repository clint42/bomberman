/*
** Filter.cpp for Filter in /home/lafitt_g/Tek2/c++/bomberman
** 
** Made by lafitt_g
** Login   <lafitt_g@lafittg>
** 
** Started on  Mon Jun  2 17:54:14 2014 lafitt_g
** Last update Mon Jun  2 18:21:00 2014 lafitt_g
*/

#include "Filter.hpp"

void
getInformation(const std::string &msg, size_t *field, size_t cur_1, size_t cur_2)
{
  if (cur_1 != std::string::npos && cur_2 != std::string::npos)
    {
      std::stringstream convert(msg.substr(cur_1, cur_2));
      convert >> *field;
    }
  else
    field = 0;
}

void
filterCmd(const t_msg &msg)
{
  t_cmd	*cmd = new t_cmd;
  size_t	cur_1 = 0;
  size_t	cur_2 = 0;

  cmd->date = msg._date;
  cur_1 = msg._msg.find(" ", cur_1);
  this->getInformation(msg._msg, &cmd->id, cur_2, cur_1);
  cur_2 = msg._msg.find(" ", cur_1 + 1);
  this->getInformation(msg._msg, &cmd->pos.first, cur_1 + 1, cur_2 - (cur_1 + 1));
  cur_1 = msg._msg.find(" ", cur_2 + 1);
  this->getInformation(msg._msg, &cmd->pos.first, cur_2 + 1, cur_1 - (cur_2 + 1));
  cur_2 = msg._msg.find(" ", cur_1 + 1);
  cmd->action = msg._msg.substr(cur_1 + 1, cur_2 - (cur_1 + 1));
  while (cur_2 != std::string::npos && cur_1 != std::string::npos)
    {
      cur_1 = msg._msg.find(" ", cur_2 + 1);
      cmd->params.push_back(msg._msg.substr(cur_2 + 1, cur_1 - (cur_2 + 1)));
      if (cur_1 != std::string::npos && (cur_2 = msg._msg.find(" ", cur_1 + 1)) != std::string::npos)
	cmd->params.push_back(msg._msg.substr(cur_1 + 1, cur_2 - (cur_1 + 1)));
    }
}
