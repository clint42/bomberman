#ifndef TIME_HPP_
# define TIME_HPP_

# include <sys/time.h>
# include <iostream>

class	Time {

  timeval _t;

public:

  // static Time now() {
  //   Time t;
  //   t.now();
  //   return t;
  // }

  Time(size_t h = 0, size_t m = 0, size_t s = 0, size_t ms = 0, size_t us = 0);
  ~Time();

  Time &		now() {
    gettimeofday(&_t, NULL);
    return *this;
  }

  size_t		hour() const {
    return _t.tv_sec / 3600;
  }
  
  size_t		min() const {
    return _t.tv_sec / 60;
  }
  
  size_t		sec() const {
    return _t.tv_sec;
  }

  unsigned long int	msec() const {
    return (_t.tv_sec * 1000) + (_t.tv_usec / 1000);
  }

  unsigned long int	usec() const {
    return (_t.tv_sec * 1000000) + _t.tv_usec;
  }

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
