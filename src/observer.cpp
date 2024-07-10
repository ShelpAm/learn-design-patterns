#include "observer.h"
#include <algorithm>
#include <iostream>

void Subject::notify() const {
  std::ranges::for_each(_observers, [](auto const &weak_observer) {
    if (auto locked{weak_observer.lock()}) {
      locked->update();
    }
  });
}

void Subject::attach(std::shared_ptr<Observer> const &observer) {
  _observers.push_back(observer);
}

void Subject::detach(std::shared_ptr<Observer> const &observer) {
  std::erase_if(_observers, [&observer](auto const &wp) {
    return wp.expired() || wp.lock() == observer;
  });
}

void King_of_glory_player::do_play() {
  _online = true;
  notify();
}

void King_of_glory_player::do_offline() {
  _online = false;
  notify();
}

void Unhappy_to_observe_subject::update() {
  std::cout << "Unhappy to observe subject... ";
  if (_subject->online()) {
    std::cout << "She is online, I know the information now.\n";
  } else {
    std::cout << "She is offline, I don't know what she is doing. :(\n";
  }
}

Teacher::Teacher(King_of_glory_player *subject) : _subject(subject) {}

void Teacher::update() {
  if (_subject->online()) {
    std::cout << "Forcing subject to offline.\n";
    _subject->do_offline();
  } else {
    std::cout << "Normal student.\n";
  }
}

Timer::Timer(std::chrono::milliseconds period)
    : _thread([this]() {
        while (!_stop) {
          auto now{std::chrono::steady_clock::now()};
          auto diff{now - _last_updated};
          if (diff > _period) {
            notify();
            _last_updated = now;
          }
        }
      }),
      _last_updated(std::chrono::steady_clock::now()), _period(period) {}

Timer::~Timer() {
  _stop = true;
  if (_thread.joinable()) {
    _thread.join();
  }
}

void Timer::run() {
  if (_thread.joinable()) {
    _thread.detach();
  } else {
    throw std::runtime_error{"Call Timer::run() more than once."};
  }
}
