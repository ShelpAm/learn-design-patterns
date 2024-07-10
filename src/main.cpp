#include "factory_method.h"
#include "observer.h"
/*#include "spdlog/spdlog.h"*/

int main() {
  // Factory method
  std::unique_ptr<Logistics> logistics{std::make_unique<Road_logistics>()};
  logistics->plan_delivery();
  logistics = std::make_unique<Sea_logistics>();
  logistics->plan_delivery();

  // Observer
  Publisher subject;
  auto me{std::make_shared<Unhappy_to_observe_subject>()};
  subject.subscribe(me);
  subject.subscribe(me);
  subject.notify_all();
}
