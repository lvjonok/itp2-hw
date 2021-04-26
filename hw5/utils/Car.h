#include <string>

#include "../database/parser.h"

#ifndef CAR_H
#define CAR_H

namespace car {

// Exception would be thrown, if car was not validated yet
class CarNotValidated {};

enum class CarType { Economy, Comfort, ComfortPlus, Business };
// Function returns string with CarType enum class
std::string serialize_car_type(CarType type) {
  switch (type) {
    case CarType::Economy:
      return "Economy";
    case CarType::Comfort:
      return "Comfort";
    case CarType::ComfortPlus:
      return "ComfortPlus";
    case CarType::Business:
      return "Business";
  }
}

class Car {
  CarType type;
  std::string model;
  std::string current_coordinates;
  std::string color;
  std::string number;
  // requirement from hw5 to validate a car before the first run
  bool validated = false;

 public:
  Car(CarType _type, std::string _model, std::string _cur_coors,
      std::string _color, std::string _number)
      : type(_type),
        model(_model),
        current_coordinates(_cur_coors),
        color(_color),
        number(_number) {}

  Car(CarType _type, std::string _model, std::string _cur_coors,
      std::string _color, std::string _number, bool _validated)
      : type(_type),
        model(_model),
        current_coordinates(_cur_coors),
        color(_color),
        number(_number),
        validated(_validated) {}

  // Constructor for Car from database entry
  Car(std::string serialized) {
    auto tokens = parser::parse_string(serialized, '/');

    if (tokens[0] == "Economy") {
      type = CarType::Economy;
    }
    if (tokens[0] == "Comfort") {
      type = CarType::Comfort;
    }
    if (tokens[0] == "ComfortPlus") {
      type = CarType::ComfortPlus;
    }
    if (tokens[0] == "Business") {
      type = CarType::Business;
    }

    model = tokens[1];
    current_coordinates = tokens[2];
    color = tokens[3];
    number = tokens[4];
    // parsing serialized boolean
    if (tokens[5] == "1") {
      validated = true;
    } else {
      validated = false;
    }
  }
  // Function returns string with Car class. Format
  // CarType/Model/Current_coordinates/Color/Number/validated
  car::CarType get_car_type() { return type; }
  // method returns whether we validated car or not
  bool is_validated() { return validated; }
  std::string serialize() {
    return serialize_car_type(type) + "/" + model + "/" + current_coordinates +
           "/" + color + "/" + number + "/" + std::to_string(validated);
  }
  // Method updates current coordinates of a car
  void set_current_coordinates(std::string _cur_coors) {
    current_coordinates = _cur_coors;
  }
  // Method returns current coordinates of a car
  std::string get_current_coordinates() { return current_coordinates; }
  void finish_ride() {}
};

class CarEconomy : public Car {
 public:
  CarEconomy(std::string _model, std::string _cur_coors, std::string _color,
             std::string _number, bool _va)
      : Car(CarType::Economy, _model, _cur_coors, _color, _number) {}

  CarEconomy(std::string serialized) : Car(serialized) {}
  // Function returns string with CarEconomy class. Format
  // CarType/Model/Current_coordinates/Color/Number
  std::string serialize() { return Car::serialize(); }
};

class CarComfort : public Car {
  // by default each car has 5 bottles of water
  int freeBottleOfwater = 5;

 public:
  CarComfort(std::string _model, std::string _cur_coors, std::string _color,
             std::string _number)
      : Car(CarType::Comfort, _model, _cur_coors, _color, _number) {}
  CarComfort(std::string _model, std::string _cur_coors, std::string _color,
             std::string _number, bool _validated)
      : Car(CarType::Comfort, _model, _cur_coors, _color, _number, _validated) {
  }
  CarComfort(std::string serialized) : Car(serialized) {
    auto tokens = parser::parse_string(serialized, '/');
    freeBottleOfwater = std::stoi(tokens[6]);
  }
  // Function returns string with CarComfort class. Format
  // CarType/Model/Current_coordinates/Color/Number/validated/freeBottleOfwater
  std::string serialize() {
    return Car::serialize() + "/" + std::to_string(freeBottleOfwater);
  }
  void finish_ride() {
    freeBottleOfwater -= std::max(0, int(static_cast<float>(rand()) /
                                         (static_cast<float>(RAND_MAX) / 5)));
  }
};

class CarComfortPlus : public Car {
  // by default each car has 10 bottles of water
  int freeBottleOfwater = 10;

 public:
  CarComfortPlus(std::string _model, std::string _cur_coors, std::string _color,
                 std::string _number)
      : Car(CarType::ComfortPlus, _model, _cur_coors, _color, _number) {}
  CarComfortPlus(std::string _model, std::string _cur_coors, std::string _color,
                 std::string _number, bool _validated)
      : Car(CarType::Comfort, _model, _cur_coors, _color, _number, _validated) {
  }
  CarComfortPlus(std::string serialized) : Car(serialized) {
    auto tokens = parser::parse_string(serialized, '/');
    freeBottleOfwater = std::stoi(tokens[6]);
  }
  // Function returns string with CarComfortPlus class. Format
  // CarType/Model/Current_coordinates/Color/Number/validated/freeBottleOfwater
  std::string serialize() {
    return Car::serialize() + "/" + std::to_string(freeBottleOfwater);
  }
  void finish_ride() {
    freeBottleOfwater -= std::max(0, int(static_cast<float>(rand()) /
                                         (static_cast<float>(RAND_MAX) / 10)));
  }
};

class CarBusiness : public Car {
  // by default each car has 50 bottles of water
  int freeBottleOfwater = 50;

 public:
  CarBusiness(std::string _model, std::string _cur_coors, std::string _color,
              std::string _number)
      : Car(CarType::ComfortPlus, _model, _cur_coors, _color, _number) {}
  CarBusiness(std::string _model, std::string _cur_coors, std::string _color,
              std::string _number, bool _validated)
      : Car(CarType::Comfort, _model, _cur_coors, _color, _number, _validated) {
  }
  CarBusiness(std::string serialized) : Car(serialized) {
    auto tokens = parser::parse_string(serialized, '/');
    freeBottleOfwater = std::stoi(tokens[6]);
  }

  // method required by task, returns result of operation
  std::string parkRightInFrontOfTheEntrance() {
    return "Car is parked in front of the entrance";
  }
  // Function returns string with CarBusiness class. Format
  // CarType/Model/Current_coordinates/Color/Number/validated/freeBottleOfwater
  std::string serialize() {
    return Car::serialize() + "/" + std::to_string(freeBottleOfwater);
  }
  void finish_ride() {
    freeBottleOfwater -= std::max(0, int(static_cast<float>(rand()) /
                                         (static_cast<float>(RAND_MAX) / 10)));
  }
};

};  // namespace car

#endif