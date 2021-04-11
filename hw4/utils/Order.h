#include <string>

#include "../database/parser.h"
#include "Address.h"
#include "Car.h"
#include "Time.h"

#ifndef ORDER_H
#define ORDER_H

// Class for each ride in system
class Order {
  Address starting_point;
  Address destination;
  car::CarType type_of_car;
  Time date;
  // Price for each ride generates randomly in range [0, 1] units
  float price;

 public:
  Order(Address _starting_point, Address _destination,
        car::CarType _type_of_car)
      : starting_point(_starting_point),
        destination(_destination),
        type_of_car(_type_of_car),
        date(Time("")) {
    price = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
    // time spend for ride can be in range [0, 120]
    date = Time(std::to_string(static_cast<float>(rand()) /
                               (static_cast<float>(RAND_MAX / 120.0))));
  }
  Order(std::string serialized) {
    auto tokens = parser::parse_string(serialized, '/');
    starting_point = Address(tokens[0]);
    destination = Address(tokens[1]);
    date = Time(tokens[2]);
    price = std::stof(tokens[3]);

    if (tokens[4] == "Economy") {
      type_of_car = car::CarType::Economy;
    }
    if (tokens[4] == "Comfort") {
      type_of_car = car::CarType::Comfort;
    }
    if (tokens[4] == "ComfortPlus") {
      type_of_car = car::CarType::ComfortPlus;
    }
    if (tokens[4] == "Business") {
      type_of_car = car::CarType::Business;
    }
  }
  std::string get_output_format() {
    return "Ride from " + starting_point.serialize() + " to " +
           destination.serialize() + ". Time spent: " + date.serialize() +
           ". Money cost: " + std::to_string(price) + ".";
  }

  // Method returns type of Car for this Ride
  car::CarType get_car_type() { return type_of_car; }

  // Method returns price for this Ride
  float get_price() { return price; }

  // Method returns time for this Ride
  Time get_time() { return date; }

  // Function returns string with Order class. Format:
  // "Address/Address/Time/Price/CarType"
  std::string serialize() {
    return starting_point.serialize() + "/" + destination.serialize() + "/" +
           date.serialize() + "/" + std::to_string(price) + "/" +
           car::serialize_car_type(type_of_car);
  }
};

#endif
