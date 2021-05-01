#include <vector>

#include "../database/parser.h"
#include "Driver.h"
#include "Order.h"
#include "Passenger.h"

#ifndef RIDE_H
#define RIDE_H

// typedef std::tuple<Order *, Passenger *, driver::Driver *, int> Ride;

class Ride {
 public:
  Order* order;
  Passenger* passenger;
  std::string passenger_name;
  driver::Driver* driver = nullptr;
  std::string driver_name;
  int payment_idx;
  Ride(Order* _order, Passenger* _passenger, driver::Driver* _driver,
       int _payment_idx)
      : order(_order),
        passenger(_passenger),
        driver(_driver),
        payment_idx(_payment_idx) {}

  Ride(std::string serialized) {
    auto tokens = parser::parse_string(serialized, ',');
    this->order = new Order(tokens[0]);
    this->passenger_name = tokens[1];
    this->driver_name = tokens[2];
    this->payment_idx = std::stoi(tokens[3]);
  }

  // Method updates missing pointers for Ride class
  void update(std::vector<Passenger*> passengers,
              std::vector<driver::Driver*> drivers) {
    for (auto passenger : passengers) {
      if (passenger->get_name() == this->passenger_name) {
        this->passenger = passenger;
      }
    }
    for (auto driver : drivers) {
      if (driver->get_name() == this->driver_name) {
        this->driver = driver;
      }
    }
  }

  // Constuctor for entry from Passenger
  Ride(std::tuple<Order*, Passenger*, driver::Driver*, int> tuple) {
    this->order = std::get<0>(tuple);
    this->passenger = std::get<1>(tuple);
    this->passenger_name = this->passenger->get_name();
    this->driver = std::get<2>(tuple);
    // this->driver_name = this->driver->get_name();
    this->payment_idx = std::get<3>(tuple);
  }

  // Constuctor for entry from database, with instant update
  Ride(std::string serialized, std::vector<Passenger*> passengers,
       std::vector<driver::Driver*> drivers) {
    auto tokens = parser::parse_string(serialized, ',');
    this->order = new Order(tokens[0]);

    this->passenger_name = tokens[1];
    for (auto passenger : passengers) {
      if (passenger_name == passenger->get_name()) {
        this->passenger = passenger;
      }
    }

    this->driver_name = tokens[2];
    for (auto driver : drivers) {
      if (driver_name == driver->get_name()) {
        this->driver = driver;
      }
    }
    this->payment_idx = std::stoi(tokens[3]);
  }

  // Method returns string representation of Ride class in csv.
  // Order/PassengerName/DriverName/PaymentIdx
  std::string serialize() {
    if (driver != 0) {
      return order->serialize() + "," + passenger_name + "," +
             driver_name + "," + std::to_string(payment_idx);
    }
    else {
      return order->serialize() + "," + passenger_name + "," + driver_name +
             "," + std::to_string(payment_idx);
    }
  }
};

#endif