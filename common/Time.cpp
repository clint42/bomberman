#include "Time.hpp"

Time::Time(size_t h, size_t m, size_t s, size_t ms, size_t us) {
  _t.tv_sec = (h * 3600) + (m * 60) + s;
  _t.tv_usec = (ms * 1000) + us;
}
Time::~Time() {
}

Time &
Time::operator=(Time const &t) {
    _t.tv_sec = t._t.tv_sec;
    _t.tv_usec = t._t.tv_usec;
    return *this;
}
Time &
Time::operator-=(Time const &t) {
  _t.tv_usec = (_t.tv_usec - t._t.tv_usec) > 0 ? (_t.tv_usec - t._t.tv_usec) : 0;
  _t.tv_sec = (_t.tv_sec - t._t.tv_sec) > 0 ? (_t.tv_sec - t._t.tv_sec) - !(_t.tv_usec) : 0;
  return *this;
}
Time &
Time::operator+=(Time const &t) {
  _t.tv_sec += t._t.tv_sec;
  if ((_t.tv_usec += t._t.tv_usec) >= 1000000) {
    _t.tv_usec %= 1000000;
    _t.tv_sec += 1;
  };
  return *this;
}

Time
Time::operator-(Time const &t) const {
  Time	ret;
  ret._t.tv_usec = (_t.tv_usec - t._t.tv_usec) > 0 ? (_t.tv_usec - t._t.tv_usec) : 0;
  ret._t.tv_sec = (_t.tv_sec - t._t.tv_sec) > 0 ? (_t.tv_sec - t._t.tv_sec) - !(ret._t.tv_usec) : 0;
  return ret;
}

Time
Time::operator+(Time const &t) const {
  Time	ret;
  ret._t.tv_sec = _t.tv_sec + t._t.tv_sec;
  if ((ret._t.tv_usec = _t.tv_usec + t._t.tv_usec) > 1000000) {
    ret._t.tv_sec += 1;
    ret._t.tv_usec %= 1000000;
  }
  return ret;
}

bool
Time::operator>(Time const &t) const {
  return this->inUsec() > t.inUsec();
}

bool
Time::operator<(Time const &t) const {
  return this->inUsec() < t.inUsec();
}

std::ostream &
operator<<(std::ostream &s, Time const &t) {
  s << "Time(h: " << t.hour() 
    << ", m: " << t.min()
    << ", s: " << t.sec()
    << " , ms: " << t.msec()
    << " , us: " << t.usec()
    << ")";
  return s;
}
