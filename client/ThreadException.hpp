//
// ThreadException.hpp for bomberman$ in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 19 14:38:38 2014 aurelien prieur
// Last update Mon May 19 14:39:20 2014 aurelien prieur
//

#ifndef THREADEXCEPTION_HPP_
# define THREADEXCEPTION_HPP_

# include <exception>

class   ThreadException: public std::exception
{
  std::string   _what;
public:
  ThreadException(std::string const &what);
  ~ThreadException() throw();
  const char    *what() const throw();
};

#endif // !THREADEXCEPTION_HPP_
