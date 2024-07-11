#include "factory_method.h"
#include <iostream>

Transport::~Transport() = default;

void Trunk::deliver() const { std::cout << "Delivering over roads.\n"; }

void Ship::deliver() const { std::cout << "Delivering over sea.\n"; }

Logistics::~Logistics() = default;

void Logistics::plan_delivery() {
  _transport = make_transport();
  _transport->deliver();
}

auto Road_logistics::make_transport() const -> std::unique_ptr<Transport> {
  return std::make_unique<Trunk>();
}

auto Sea_logistics::make_transport() const -> std::unique_ptr<Transport> {
  return std::make_unique<Ship>();
}
