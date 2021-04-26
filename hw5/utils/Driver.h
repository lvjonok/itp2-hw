#include <algorithm>
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
  // remove as deprecated
  // car::Car* car;

  // points to currrently selected car of user
  car::Car* current_car;
  // Collection of driver cars
  std::vector<car::Car*> cars;

  // Regarding task description status can be:
  // Working, NotWorking, OnRide, NotOnRide
  DriverStatus status;

 private:
  // separated constructor for parser
  car::Car* parse_car(std::string entry) {
    auto car_type = parser::parse_string(entry, '/')[0];
    if (car_type == "Economy") {
      return new car::CarEconomy(entry);
    }
    if (car_type == "Comfort") {
      return new car::CarComfort(entry);
    }
    if (car_type == "ComfortPlus") {
      return new car::CarComfortPlus(entry);
    }
    if (car_type == "Business") {
      return new car::CarBusiness(entry);
    }
  }
  // separated constructor for serialized car
  std::string serialize_car(car::Car* _car) {
    switch (_car->get_car_type()) {
      case (car::CarType::Economy):
        return ((car::CarEconomy*)_car)->serialize();
      case (car::CarType::Comfort):
        return ((car::CarComfort*)_car)->serialize();
      case (car::CarType::ComfortPlus):
        return ((car::CarComfortPlus*)_car)->serialize();
      case (car::CarType::Business):
        return ((car::CarBusiness*)_car)->serialize();
    }
  }

 public:
  Driver(std::string _name, float _rating, std::vector<car::Car*> _cars,
         car::Car* _current_car,
         DriverStatus _status = DriverStatus::NotWorking)
      : name(_name),
        rating(_rating),
        cars(_cars),
        current_car(_current_car),
        status(_status) {}
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

    for (auto car_entry : parser::parse_string(tokens[3], ':')) {
      this->cars.push_back(parse_car(car_entry));
    }
    this->current_car = this->cars[stoi(tokens[4])];
  }
  // Method returns string as csv to write in database
  // Name,Rating,Status,Cars,selectedCar
  std::string serialize() {
    // upcasting car
    std::string entry = name + "," + std::to_string(rating) + "," +
                        serialize_driver_status(status) + ",";

    for (auto it = cars.begin(); it != cars.end(); it++) {
      auto current_car = *it;
      if (it != cars.begin()) {
        entry += ":";
      }
      entry += serialize_car(current_car);
    }
    // store index of current car
    entry += "," + std::to_string(std::distance(
                       cars.begin(),
                       std::find(cars.begin(), cars.end(), current_car)));
    return entry;
  }
  // Method updates current status of Driver.
  void update_status(DriverStatus _status) { status = _status; }
  // Method returns current status of Driver.
  DriverStatus get_status() { return status; }
  // Method returns history of orders for Driver
  std::vector<Order*> get_order_history() { return order_history; }
  // Method returns car of Driver to see it
  car::Car* get_car() { return current_car; }
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
      if (order->order->get_car_type() == this->current_car->get_car_type()) {
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
    current_car->set_current_coordinates(std::to_string(new_coordinates));
    // return new randomized coordinates
    return current_car->get_current_coordinates();
  }
  // Method allows the driver to select one of his cars for current work
  void select_car(int idx) {
    // check for correctness of idx
    if (idx < 0 || idx >= cars.size()) return;
    current_car = cars[idx];
  }
};
};  // namespace driver

#endif