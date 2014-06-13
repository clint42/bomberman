#ifndef TIME_HPP_
# define TIME_HPP_

#include <sys/time.h>

class	Time {

  timeval _t;

public:

  // static Time now() {
  //   Time t;
  //   t.now();
  //   return t;
  // }

  Time(size_t h = 0, size_t m = 0, size_t s = 0, size_t ms = 0, size_t us = 0) {
    _t.tv_sec = (h * 3600) + (m * 60) + s;
    _t.tv_usec = (ms * 1000) + us;
  }
  ~Time() { }

  Time &		now() {
    gettimeofday(&_t, NULL);
    return *this;
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

  Time &	operator=(Time const &t) {
    _t.tv_sec = t._t.tv_sec;
    _t.tv_usec = t._t.tv_usec;
    return *this;
  }
  Time &	operator-=(Time const &t) {
    _t.tv_sec = (_t.tv_sec - t._t.tv_sec) > 0 ? (_t.tv_sec - t._t.tv_sec) : 0;
    _t.tv_usec = (_t.tv_usec - t._t.tv_usec) > 0 ? (_t.tv_usec - t._t.tv_usec) : 0;
    return *this;
  }
  Time &	operator+=(Time const &t) {
    _t.tv_sec += t._t.tv_sec;
    _t.tv_usec += t._t.tv_usec;
    return *this;
  }

  Time		operator-(Time const &t) const {
    Time	ret;
    ret._t.tv_sec = (_t.tv_sec - t._t.tv_sec) > 0 ? (_t.tv_sec - t._t.tv_sec) : 0;
    ret._t.tv_usec = (_t.tv_usec - t._t.tv_usec) > 0 ? (_t.tv_usec - t._t.tv_usec) : 0;
    return ret;
  }

  Time		operator+(Time const &t) const {
    Time	ret;
    ret._t.tv_sec = _t.tv_sec + t._t.tv_sec;
    ret._t.tv_usec = _t.tv_usec + t._t.tv_usec;
    return ret;
  }

  bool		operator>(Time const &t) const {
    return this->usec() > t.usec();
  }

  bool		operator<(Time const &t) const {
    return this->usec() < t.usec();
  }

};

#endif /* !TIME_HPP_ */
