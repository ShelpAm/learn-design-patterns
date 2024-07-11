#pragma once
#include <memory>

class Transport {
public:
  Transport() = default;
  Transport(const Transport &) = default;
  Transport(Transport &&) = default;
  auto operator=(const Transport &) -> Transport & = default;
  auto operator=(Transport &&) -> Transport & = default;
  virtual ~Transport() = 0;

  virtual void deliver() const = 0;
};

class Trunk : public Transport {
  void deliver() const override;
};

class Ship : public Transport {
  void deliver() const override;
};

class Logistics {
public:
  Logistics() = default;
  Logistics(const Logistics &) = delete;
  Logistics(Logistics &&) = delete;
  auto operator=(const Logistics &) -> Logistics & = delete;
  auto operator=(Logistics &&) -> Logistics & = delete;
  virtual ~Logistics() = 0;

  void plan_delivery();

private:
  [[nodiscard]] virtual auto
  make_transport() const -> std::unique_ptr<Transport> = 0;
  std::unique_ptr<Transport> _transport;
};

class Road_logistics : public Logistics {
private:
  [[nodiscard]] auto
  make_transport() const -> std::unique_ptr<Transport> override;
};

class Sea_logistics : public Logistics {
  [[nodiscard]] auto
  make_transport() const -> std::unique_ptr<Transport> override;
};
