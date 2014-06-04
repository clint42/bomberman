//
// Exception.hpp for  in /home/franel_j/tek2/cpp/bomberman/common
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Tue May  6 11:11:14 2014 julie franel
// Last update Tue Jun  3 16:56:29 2014 aurelien prieur
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

class		ConnexionException : public ABombermanException {
public:
  ConnexionException(std::string const &) throw ();
  virtual ~ConnexionException() throw ();
};

#endif /* !EXCEPTION_HPP_ */
