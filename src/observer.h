#pragma once
#include <iostream>
#include <memory>
#include <vector>

class Subscriber {
public:
  virtual ~Subscriber() = default;
  virtual void update() = 0;
};

class Publisher {
public:
  void notify_all() const {
    for (auto const &subscriber : _subscribers) {
      if (auto const ptr{subscriber.lock()}; ptr) {
        ptr->update();
      }
    }
  }

  void subscribe(std::shared_ptr<Subscriber> const &subscriber) {
    _subscribers.push_back(subscriber);
  }

  void unsubscribe(std::shared_ptr<Subscriber> const &subscriber) {
    std::erase_if(_subscribers, [&subscriber](auto const &wp) {
      return wp.expired() || wp.lock() == subscriber;
    });
  }

private:
  std::vector<std::weak_ptr<Subscriber>> _subscribers;
};

class Unhappy_to_observe_subject : public Subscriber {
public:
  void update() override { std::cout << "Unhappy to observe subject...\n"; }
};
