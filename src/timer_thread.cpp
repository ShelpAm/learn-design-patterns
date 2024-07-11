#include "timer_thread.h"

Timer_thread::Timer_thread(std::chrono::nanoseconds period,
                           std::function<void()> function)
    : _thread([this, func = std::move(function)]() {
        while (!_stop) {
          auto now{std::chrono::steady_clock::now()};
          auto diff{now - _last_updated};
          if (diff > _period) {
            func();
            _last_updated = now;
          }
        }
      }),
      _period(period), _last_updated(std::chrono::steady_clock::now()) {}

Timer_thread::~Timer_thread() { stop(); }

void Timer_thread::start() {
  if (_thread.joinable()) {
    _thread.detach();
  } else {
    throw std::runtime_error{"Timer thread is already running."};
  }
}

void Timer_thread::stop() {
  _stop = true;
  if (_thread.joinable()) {
    _thread.join();
  }
}
