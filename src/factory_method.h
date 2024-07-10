#pragma once
#include <iostream>
#include <memory>

class Transport {
public:
  Transport() = default;
  Transport(const Transport &) = default;
  Transport(Transport &&) = default;
  Transport &operator=(const Transport &) = default;
  Transport &operator=(Transport &&) = default;
  virtual ~Transport() = 0;

  virtual void deliver() const = 0;
};
Transport::~Transport() = default;

class Trunk : public Transport {
  void deliver() const override { std::cout << "Delivering over roads.\n"; }
};

class Ship : public Transport {
  void deliver() const override { std::cout << "Delivering over sea.\n"; }
};

class Logistics {
public:
  Logistics() = default;
  Logistics(const Logistics &) = delete;
  Logistics(Logistics &&) = delete;
  Logistics &operator=(const Logistics &) = delete;
  Logistics &operator=(Logistics &&) = delete;
  virtual ~Logistics() = 0;

  void plan_delivery() {
    _transport = make_transport();
    _transport->deliver();
  }

private:
  [[nodiscard]] virtual std::unique_ptr<Transport> make_transport() const = 0;
  std::unique_ptr<Transport> _transport;
};
Logistics::~Logistics() = default;

class Road_logistics : public Logistics {
private:
  [[nodiscard]] std::unique_ptr<Transport> make_transport() const override {
    return std::make_unique<Trunk>();
  }
};

class Sea_logistics : public Logistics {
  [[nodiscard]] std::unique_ptr<Transport> make_transport() const override {
    return std::make_unique<Ship>();
  }
};
