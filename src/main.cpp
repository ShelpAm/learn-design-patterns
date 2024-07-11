/*#include "factory_method.h"*/
#include "observer.h"
#include <iostream>
#include <thread>
/*#include "spdlog/spdlog.h"*/

int main() {
  // Factory method
  /*std::unique_ptr<Logistics> logistics{std::make_unique<Road_logistics>()};*/
  /*logistics->plan_delivery();*/
  /*logistics = std::make_unique<Sea_logistics>();*/
  /*logistics->plan_delivery();*/

  // Observer
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
  Timer t{1000ms};
  t.attach(me);
  t.run();

  Timer t1{100'000'000ns};
  t1.attach(teacher);
  t1.attach(me);
  t1.run();

  // Blocks timers
  while (true) {
  }

  return 0;
}
