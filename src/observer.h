#pragma once
#include <chrono>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

class Subject;

class Observer {
public:
  virtual ~Observer() = default;
  virtual void update() = 0;
};

class Subject {
public:
  void attach(std::shared_ptr<Observer> const &);
  void detach(std::shared_ptr<Observer> const &);
  void notify() const;

private:
  std::vector<std::weak_ptr<Observer>> _observers;
};

class King_of_glory_player : public Subject {
public:
  void up_account();
  void down_account();
  [[nodiscard]] bool online() const;

private:
  bool _online{};
};

class Unhappy_to_observe_subject : public Observer {
public:
  Unhappy_to_observe_subject(King_of_glory_player const *subject);
  void update() override;

private:
  King_of_glory_player const *_subject;
};

class Teacher : public Observer {
public:
  Teacher(King_of_glory_player *);
  void update() override;

private:
  King_of_glory_player *_subject;
};

class Timer_thread {
public:
  Timer_thread(Timer_thread const &) = delete;
  Timer_thread(Timer_thread &&) = delete;
  Timer_thread &operator=(Timer_thread const &) = delete;
  Timer_thread &operator=(Timer_thread &&) = delete;
  Timer_thread(std::chrono::nanoseconds period, std::function<void()> function);
  ~Timer_thread();
  void start();
  void stop();

private:
  std::atomic<bool> _stop;
  std::thread _thread;
  std::chrono::nanoseconds _period;
  std::chrono::time_point<std::chrono::steady_clock> _last_updated;
};

class Timer : public Subject {
public:
  Timer(std::chrono::nanoseconds period);

  // You are not allowed to call this more than once.
  void run();

private:
  Timer_thread _timer_thread;
};
