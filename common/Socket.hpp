#ifndef SOCKET_HPP_
# define SOCKET_HPP_

# include <unistd.h>
# include <iostream>
# include <ext/stdio_filebuf.h>
# include <vector>
# include <string>
# include "Time.hpp"
# include "macros.hpp"

class Socket {

  __gnu_cxx::stdio_filebuf<char> * __in;
  __gnu_cxx::stdio_filebuf<char> * __out;
  std::istream *		   _in;
  std::ostream *		   _out;
  int				   _fd;

public:
  Socket(int fd) {
    __in = new __gnu_cxx::stdio_filebuf<char>(fd, std::ios::in);
    __out = new __gnu_cxx::stdio_filebuf<char>(fd, std::ios::out);

    _fd = fd;
    _in = new std::istream(__in);
    _out = new std::ostream(__out);
  }
  ~Socket() { delete _in; delete _out; delete __in; delete __out; close(_fd); }

  inline int  getFd() const { return _fd; }
  inline void write(std::string const &toWrite) { *_out << toWrite << std::flush; }

  inline void getLine(std::string &toFill) { std::getline(*_in, toFill); }
  void	      getLine(std::vector<std::string *> &toFill) {
    //DEBUG("Socket::getLine()", 1);
    while (_in->peek() != -1) {
      //DEBUG("Socket::getLine() => loop", 1);
      std::string *m = new std::string;
      std::getline(*_in, *m);
      toFill.push_back(m);
      //DEBUG("Socket::getLine() => ! loop", -1);
      if (_in->peek() == '\n')
      	_in->get();
    }
    _in->clear();
    //DEBUG("! Socket::getLine()", -1);
  }
  
  inline bool read(std::string &toFill) {
    std::string	tmp;

    while (_in->peek() != -1)
      {
    	std::getline(*_in, tmp);
    	toFill += tmp + "\n";
      }
    _in->clear();
    return (true);
  }
};

#endif /* !SOCKET_HPP_ */
