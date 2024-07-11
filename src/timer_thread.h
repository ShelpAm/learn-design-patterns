#pragma once
#include <atomic>
#include <chrono>
#include <functional>
#include <thread>

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
