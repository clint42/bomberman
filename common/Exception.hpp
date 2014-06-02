//
// Exception.hpp for  in /home/franel_j/tek2/cpp/bomberman/common
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Tue May  6 11:11:14 2014 julie franel
// Last update Mon Jun  2 14:09:56 2014 julie franel
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

class		MapException : public ABombermanException
{
public:
  MapException(const std::string &msg) throw();
  virtual ~MapException(void) throw();
};

class		SocketException : public ABombermanException
{
public:
  SocketException(const std::string &msg) throw();
  virtual ~SocketException(void) throw();
};

class		ServerException : public ABombermanException
{
public:
  ServerException(const std::string &msg) throw();
  virtual ~ServerException(void) throw();
};

#endif /* !EXCEPTION_HPP_ */
