//
// Exception.hpp for  in /home/franel_j/tek2/cpp/bomberman/common
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Tue May  6 11:11:14 2014 julie franel
// Last update Fri Jun 13 15:16:10 2014 julie franel
//

#ifndef EXCEPTION_HPP_
# define EXCEPTION_HPP_

# include <exception>
# include <string>

class		ABombermanException : public std::exception
{
private:
  std::string	_message;

public:
  ABombermanException(std::string const &) throw();
  virtual ~ABombermanException(void) throw();

  virtual const char *what(void) const throw();
};


#endif /* !EXCEPTION_HPP_ */
