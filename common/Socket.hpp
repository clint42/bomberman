//
// Socket.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Thu May 22 14:42:09 2014 buret_j
// Last update Thu Jun 12 13:43:33 2014 buret_j
//

#ifndef SOCKET_HPP_
# define SOCKET_HPP_

# include <unistd.h>
# include <iostream>
# include <ext/stdio_filebuf.h>

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
  inline void write(std::string const &toWrite) { *_out << toWrite << std::endl; }
  inline bool getLine(std::string &toFill) {
    return !(getline(*_in, toFill).rdstate() & std::ifstream::failbit);
  }
};

#endif /* !SOCKET_HPP_ */
