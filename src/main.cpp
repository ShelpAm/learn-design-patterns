#include "factory_method.h"
#include "observer.h"
#include <iostream>
/*#include "spdlog/spdlog.h"*/

void factory_method_demo() {
  std::unique_ptr<Logistics> logistics{std::make_unique<Road_logistics>()};
  logistics->plan_delivery();
  logistics = std::make_unique<Sea_logistics>();
  logistics->plan_delivery();
}

void observer_demo() {
  King_of_glory_player she;
  auto me{std::make_shared<Unhappy_to_observe_subject>(&she)};
  auto teacher{std::make_shared<Teacher>(&she)};

  she.attach(teacher);
  /*she.detach(teacher);*/
  she.attach(me);

  she.up_account();
  she.down_account();
  she.up_account();

  using namespace std::chrono_literals;
  Timer t{1s};
  t.attach(me);
  t.run();

  Timer t1{1s};
  t1.attach(teacher);
  t1.attach(me);
  t1.run();
  // Blocks main thread
  while (true) {
  }
}

void timer_thread_test() {
  Timer_thread t{
      std::chrono::nanoseconds{100'000'000}, []() {
        auto now{std::chrono::steady_clock::now().time_since_epoch().count()};
        std::cout << "Tick. It's " << now << " since epoch.\n";
      }};
  t.start();
  // Blocks main thread
  while (true) {
  }
}

auto main() -> int {
  timer_thread_test();
  /*observer_demo();*/
  return 0;
}
