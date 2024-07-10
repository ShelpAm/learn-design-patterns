#pragma once
#include <chrono>
#include <memory>
#include <thread>
#include <vector>

class Subject;

class Observer {
public:
  virtual ~Observer() = default;
  virtual void update() = 0;

protected:
  Observer() = default;
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
  void do_play();

  void do_offline();

  [[nodiscard]] bool online() const { return _online; }

private:
  bool _online{};
};

class Unhappy_to_observe_subject : public Observer {
public:
  Unhappy_to_observe_subject(King_of_glory_player const *subject)
      : _subject(subject) {}

  void update() override;

private:
  King_of_glory_player const *_subject;
};

class Teacher : public Observer {
public:
  Teacher(King_of_glory_player *subject);

  void update() override;

private:
  King_of_glory_player *_subject;
};

class Timer : public Subject {
public:
  Timer(const Timer &) = delete;
  Timer(Timer &&) = delete;
  Timer &operator=(const Timer &) = delete;
  Timer &operator=(Timer &&) = delete;
  Timer(std::chrono::milliseconds period);
  ~Timer();

  // You are not allowed to call this more than once.
  void run();

private:
  std::atomic<bool> _stop;
  std::thread _thread;
  std::chrono::time_point<std::chrono::steady_clock> _last_updated;
  std::chrono::milliseconds _period;
};
