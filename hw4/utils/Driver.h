#include <string>
#include <vector>

#include "../database/parser.h"
#include "Car.h"
#include "Order.h"

#ifndef DRIVER_H
#define DRIVER_H

namespace driver {
// Modification of Driver status from task description. I found it more rational
// to have 3 statuses. If worker is on ride, if he is waiting, or he is not
// working.
enum class DriverStatus { OnRide, Working, NotWorking };
//
std::string serialize_driver_status(DriverStatus status) {
  switch (status) {
    case DriverStatus::OnRide:
      return "OnRide";
    case DriverStatus::Working:
      return "Working";
    case DriverStatus::NotWorking:
      return "NotWorking";
  }
}

class Driver {
  std::string name;
  float rating;
  std::vector<Order*> order_history;
  car::Car* car;

  // Regarding task description status can be:
  // Working, NotWorking, OnRide, NotOnRide
  DriverStatus status;

 public:
  Driver(std::string _name, float _rating, car::Car* _car,
         DriverStatus _status = DriverStatus::NotWorking)
      : name(_name), rating(_rating), car(_car), status(_status) {}
  Driver(std::string serialized) {
    auto tokens = parser::parse_string(serialized, ',');
    this->name = tokens[0];
    this->rating = std::stof(tokens[1]);

    if (tokens[2] == "OnRide") {
      this->status = DriverStatus::OnRide;
    }
    if (tokens[2] == "Working") {
      this->status = DriverStatus::Working;
    }
    if (tokens[2] == "NotWorking") {
      this->status = DriverStatus::NotWorking;
    }

    // create car from given string token
    auto car_type = parser::parse_string(tokens[3], '/')[0];
    if (car_type == "Economy") {
      this->car = new car::CarEconomy(tokens[3]);
    }
    if (car_type == "Comfort") {
      this->car = new car::CarComfort(tokens[3]);
    }
    if (car_type == "ComfortPlus") {
      this->car = new car::CarComfortPlus(tokens[3]);
    }
    if (car_type == "Business") {
      this->car = new car::CarBusiness(tokens[3]);
    }
  }
  // Method returns string as csv to write in database
  std::string serialize() {
    // upcasting car
    // auto temp_car = car;
    car::Car* temp_car;
    switch (car->get_car_type()) {
      case (car::CarType::Economy):
        return name + "," + std::to_string(rating) + "," +
               serialize_driver_status(status) + "," +
               ((car::CarEconomy*)car)->serialize();
      case (car::CarType::Comfort):
        // temp_car = ((car::CarComfort*)car);
        return name + "," + std::to_string(rating) + "," +
               serialize_driver_status(status) + "," +
               ((car::CarComfort*)car)->serialize();
      case (car::CarType::ComfortPlus):
        // temp_car = ((car::CarComfortPlus*)car);
        return name + "," + std::to_string(rating) + "," +
               serialize_driver_status(status) + "," +
               ((car::CarComfortPlus*)car)->serialize();
      case (car::CarType::Business):
        // temp_car = ((car::CarBusiness*)car);
        return name + "," + std::to_string(rating) + "," +
               serialize_driver_status(status) + "," +
               ((car::CarBusiness*)car)->serialize();
    }
  }
  // Method updates current status of Driver.
  void update_status(DriverStatus _status) { status = _status; }
  // Method returns current status of Driver.
  DriverStatus get_status() { return status; }
  // Method returns history of orders for Driver
  std::vector<Order*> get_order_history() { return order_history; }
  // Method returns car of Driver to see it
  car::Car* get_car() { return car; }
  // Method returns name of Driver
  std::string get_name() { return name; }
  // Method allows to check available orders, accept or decline it.
  // In my implementation all drivers will accept orders, if they exist
  template <class T>
  T* choose_order(std::vector<T*> available_orders) {
    this->update_status(DriverStatus::Working);
    std::vector<T*> orders_level;
    // we filter orders such that driver could accept them
    for (auto order : available_orders) {
      if (order->order->get_car_type() == this->car->get_car_type()) {
        orders_level.push_back(order);
      }
    }
    if (orders_level.size() > 0) return orders_level[0];
    // There are no available orders
    return nullptr;
  }
  // Method returns current coordinates during the ride.
  // To make system more respondible, I random coordinates of car here, and
  // return updated. Coordinates is simply the string with float value.
  std::string get_current_coordinates() {
    // coordinates in raw is float in range [0, 10]
    float new_coordinates =
        static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 10.0));
    car->set_current_coordinates(std::to_string(new_coordinates));
    // return new randomized coordinates
    return car->get_current_coordinates();
  }
};
};  // namespace driver

#endif