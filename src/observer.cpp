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

void King_of_glory_player::up_account() {
  _online = true;
  notify();
}

void King_of_glory_player::down_account() {
  _online = false;
  notify();
}

bool King_of_glory_player::online() const { return _online; }

Unhappy_to_observe_subject::Unhappy_to_observe_subject(
    King_of_glory_player const *subject)
    : _subject(subject) {}

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
    _subject->down_account();
  } else {
    std::cout << "Normal student.\n";
  }
}

Timer::Timer(std::chrono::nanoseconds period)
    : _timer_thread(period, [this] { notify(); }) {}

void Timer::run() { _timer_thread.start(); }
