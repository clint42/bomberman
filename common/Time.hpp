#ifndef TIME_HPP_
# define TIME_HPP_

# include <sys/time.h>
# include <iostream>

class	Time {

  timeval _t;

public:

  Time(size_t h = 0, size_t m = 0, size_t s = 0, size_t ms = 0, size_t us = 0);
  ~Time();

  Time &		now() {
    gettimeofday(&_t, NULL);
    return *this;
  }

  size_t		inHour() const { return _t.tv_sec / 3600; }
  size_t		hour() const { return _t.tv_sec / 3600; }
  
  size_t		inMin() const { return _t.tv_sec / 60; }
  size_t		min() const {
    return (_t.tv_sec / 60) - (this->hour() * 60);
  }
  
  size_t		inSec() const { return _t.tv_sec; }
  size_t		sec() const {
    return _t.tv_sec - (this->inMin() * 60);
  }

  unsigned long int	inMsec() const { return (_t.tv_sec * 1000) + (_t.tv_usec / 1000); }
  size_t		msec() const { return (_t.tv_usec / 1000); }

  unsigned long int	inUsec() const { return (_t.tv_sec * 1000000) + _t.tv_usec; }
  size_t		usec() const { return (_t.tv_usec % 1000); }

  Time &	operator=(Time const &t);
  Time &	operator-=(Time const &t);
  Time &	operator+=(Time const &t);
  Time		operator-(Time const &t) const;
  Time		operator+(Time const &t) const;
  bool		operator>(Time const &t) const;
  bool		operator<(Time const &t) const;

};

std::ostream &	operator<<(std::ostream &s, Time const &t);


#endif /* !TIME_HPP_ */
