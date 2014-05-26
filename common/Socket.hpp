//
// Socket.hpp for  in /home/buret_j/rendu/bomberman
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Thu May 22 14:42:09 2014 buret_j
// Last update Mon May 26 18:28:58 2014 buret_j
//

#ifndef SOCKET_HPP_
# define SOCKET_HPP_

# define SOCKET_BUFLEN 500

class Socket {

  std::istream *	_in;
  std::ostream *	_out;
  int			_fd;

public:
  Socket(int fd) {
    __gnu_cxx::stdio_filebuf<char> in(fd, std::ios:in, false, SOCKET_BUFLEN);
    __gnu_cxx::stdio_filebuf<char> out(fd, std::ios::out, false, SOCKET_BUFLEN);

    _fd = fd;
    _in = new std::istream(in);
    _out = new std::ostream(out);
  }
  ~Socket() { close(_fd); }

  inline int  getFd() const { return _fd; }
  inline void getLine(std::string &toFill) { getline(*_in, toFill); }
  inline void write(std::string const &toWrite) { _out << toWrite << std::endl; }
};

#endif /* !SOCKET_HPP_ */
