#include <algorithm>
#include <tuple>
#include <vector>

#include "Driver.h"
#include "Order.h"
#include "Passenger.h"
#include "Ride.h"

#ifndef SYSTEM_H
#define SYSTEM_H

class Gateway {
 public:
  std::vector<driver::Driver*> drivers;
  std::vector<Passenger*> passengers;
  std::vector<Ride*> rides_pending;
  std::vector<Ride*> rides_completed;
  Gateway(std::vector<driver::Driver*> _drivers,
          std::vector<Passenger*> _passengers,
          std::vector<Ride*> _rides_pending,
          std::vector<Ride*> _rides_completed)
      : drivers(_drivers),
        passengers(_passengers),
        rides_pending(_rides_pending),
        rides_completed(_rides_completed) {
    // Update all ride classes with pointers
    for (auto ride : rides_pending) {
      ride->update(passengers, drivers);
    }
    for (auto ride : rides_completed) {
      ride->update(passengers, drivers);
      for (auto passenger : passengers) {
        if (passenger->get_name() == ride->passenger_name) {
          passenger->add_order_to_history(ride->order);
        }
      }
    }
  }
};

// Class is simply interface for interacting for passengers
class PassengerGateway {
  Gateway* system;

 public:
  PassengerGateway(Gateway* _system) : system(_system) {}
  // Method to add order to main system
  void add_ride(Ride* _ride) {
    if (_ride->order != nullptr) system->rides_pending.push_back(_ride);
  }
  std::string get_current_coordinates(Ride* _ride) {
    return _ride->driver->get_current_coordinates();
  }
  bool ask_for_special_parking(Ride* _ride) {
    auto order = _ride->order;
    auto driver = _ride->driver;

    if (order->get_car_type() != car::CarType::Business) {
      // Type is not business
      return false;
    } else {
      ((car::CarBusiness*)(driver->get_car()))->parkRightInFrontOfTheEntrance();
      return true;
    }
  }
};

// Class is simply interface for interacting for drivers
class DriverGateway {
  Gateway* system;

 public:
  DriverGateway(Gateway* _system) : system(_system) {}
  // Method will give driver available rides to accept
  std::vector<Ride*> get_available_rides() { return system->rides_pending; }

  void take_ride(Ride* _ride, driver::Driver* _driver) {
    // if driver took his ride, we mark it
    _ride->driver = _driver;
    _ride->driver_name = _driver->get_name();
    _driver->update_status(driver::DriverStatus::OnRide);
    system->rides_pending.erase(std::remove(system->rides_pending.begin(),
                                            system->rides_pending.end(), _ride),
                                system->rides_pending.end());
  }

  // Method to take order
  void complete_ride(Ride* _ride) {
    // Unpacking tuple
    auto order = _ride->order;
    auto passenger = _ride->passenger;
    auto driver = _ride->driver;
    auto payment_idx = _ride->payment_idx;

    passenger->pay(payment_idx, order->get_price());

    // Finish of ride for some cars will decrease number of free bottles
    switch (order->get_car_type()) {
      case (car::CarType::Economy):
        ((car::CarEconomy*)(driver->get_car()))->finish_ride();
        break;
      case (car::CarType::Comfort):
        ((car::CarComfort*)(driver->get_car()))->finish_ride();
        break;
      case (car::CarType::ComfortPlus):
        ((car::CarComfortPlus*)(driver->get_car()))->finish_ride();
        break;
      case (car::CarType::Business):
        ((car::CarBusiness*)(driver->get_car()))->finish_ride();
        break;
    }
    system->rides_completed.push_back(_ride);
    driver->update_status(driver::DriverStatus::Working);
    passenger->add_order_to_history(order);
  }
};

#endif