//
// Exception.hpp for  in /home/franel_j/tek2/cpp/bomberman/common
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Tue May  6 11:11:14 2014 julie franel
// Last update Tue May  6 11:12:00 2014 julie franel
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

  virtual std::string const &message(void) const throw();
};

class		Md5Exception : public ABombermanException
{
public:
  Md5Exception(void) throw();
  virtual ~Md5Exception(void) throw();
};

class		SizeException : public ABombermanException
{
public:
  SizeException(void) throw();
  virtual ~SizeException(void) throw();
};

#endif /* !EXCEPTION_HPP_ */
