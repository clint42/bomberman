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
  _t.tv_sec = (_t.tv_sec - t._t.tv_sec) > 0 ? (_t.tv_sec - t._t.tv_sec) : 0;
  _t.tv_usec = (_t.tv_usec - t._t.tv_usec) > 0 ? (_t.tv_usec - t._t.tv_usec) : 0;
  return *this;
}
Time &
Time::operator+=(Time const &t) {
  _t.tv_sec += t._t.tv_sec;
  _t.tv_usec += t._t.tv_usec;
  return *this;
}

Time
Time::operator-(Time const &t) const {
  Time	ret;
  ret._t.tv_sec = (_t.tv_sec - t._t.tv_sec) > 0 ? (_t.tv_sec - t._t.tv_sec) : 0;
  ret._t.tv_usec = (_t.tv_usec - t._t.tv_usec) > 0 ? (_t.tv_usec - t._t.tv_usec) : 0;
  return ret;
}

Time
Time::operator+(Time const &t) const {
  Time	ret;
  ret._t.tv_sec = _t.tv_sec + t._t.tv_sec;
  ret._t.tv_usec = _t.tv_usec + t._t.tv_usec;
  return ret;
}

bool
Time::operator>(Time const &t) const {
  return this->usec() > t.usec();
  }

bool
Time::operator<(Time const &t) const {
  return this->usec() < t.usec();
}



std::ostream &	operator<<(std::ostream &s, Time const &t) {
  // s << "Time(h: " << t.hour() << ", m: " << t.min() - (t.hour() * 60) << ", s: " << t.sec() - (t.min() * 60) << " , ms: " << t.msec() - (t.sec() * 1000) << " , us: " << t.usec() - (t.msec() * 1000) << ")";
  (void)t;
  return s;
}
