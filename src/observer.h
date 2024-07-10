#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Observer {
public:
  virtual ~Observer() = default;

  virtual void update() = 0;
};

class Subject {
public:
  void notify() const {
    std::ranges::for_each(_observers, [](auto const &weak_observer) {
      if (auto const ptr{weak_observer.lock()}; ptr) {
        ptr->update();
      }
    });
  }

  void attach(std::shared_ptr<Observer> const &observer) {
    _observers.push_back(observer);
  }

  void detach(std::shared_ptr<Observer> const &observer) {
    std::erase_if(_observers, [&observer](auto const &wp) {
      return wp.expired() || wp.lock() == observer;
    });
  }

private:
  std::vector<std::weak_ptr<Observer>> _observers;
};

class Unhappy_to_observe_subject : public Observer {
public:
  void update() override { std::cout << "Unhappy to observe subject...\n"; }
};
