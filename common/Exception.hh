#ifndef EXCEPTION_HH_
# define EXCEPTION_HH_

# include <exception>
# include <string>

class AbstractVMException : public std::exception
{
private:
  std::string	_message;

public:
  ABombermanException(std::string const &) throw();
  virtual ~ABombermanException(void) throw();

  virtual std::string const &message(void) const throw();
};

class Md5Exception : public ABombermanException
{
public:
  Md5Exception(void) throw();
  virtual ~Md5Exception(void) throw();
};

#endif
