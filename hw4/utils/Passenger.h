#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "../database/parser.h"
#include "Address.h"
#include "Car.h"
#include "Driver.h"
#include "Order.h"
#include "PaymentMethods.h"

#ifndef PASSENGER_H
#define PASSENGER_H

class Passenger {
  std::string name;
  float rating;
  std::vector<Order *> order_history;
  std::vector<payment::Payment *> payment_methods;
  std::vector<Address *> pinned_addresses;

 public:
  Passenger(std::string _name, float _rating,
            std::vector<payment::Payment *> _payment_methods,
            std::vector<Address *> _pinned_addresses)
      : name(_name),
        rating(_rating),
        payment_methods(_payment_methods),
        pinned_addresses(_pinned_addresses) {}

  Passenger(std::string serialized) {
    auto tokens = parser::parse_string(serialized, ',');
    this->name = tokens[0];
    this->rating = std::stof(tokens[1]);
    auto payments_methods_tokens = parser::parse_string(tokens[2], '/');
    for (int i = 0; i < payments_methods_tokens.size() - 1; i += 2) {
      this->payment_methods.push_back(new payment::Payment(
          payments_methods_tokens[i] + "/" + payments_methods_tokens[i + 1]));
    }

    auto pinned_addresses_tokens = parser::parse_string(tokens[3], '/');
    for (int i = 0; i < pinned_addresses_tokens.size(); i++) {
      pinned_addresses.push_back(new Address(pinned_addresses_tokens[i]));
    }
  }

  // Method serializes Passenger class to csv for database format
  std::string serialize() {
    // we will combine all payment methods in one "object"
    std::string payment_methods_str = "";
    for (auto payment_method : payment_methods) {
      payment_methods_str += payment_method->serialize() + "/";
    }
    // we will combine all addresses in one "object"
    std::string pinned_addresses_str = "";
    for (auto pinned_address : pinned_addresses) {
      pinned_addresses_str += pinned_address->serialize() + "/";
    }
    return name + "," + std::to_string(rating) + "," + payment_methods_str +
           "," + pinned_addresses_str;
  }

  // Method returns history of orders for this Passenger
  std::vector<Order *> get_order_history() { return order_history; }
  // Method adds a new order to history of this user
  void add_order_to_history(Order *new_order) {
    order_history.push_back(new_order);
  }
  // Method returns name of Passenger
  std::string get_name() { return name; }

  // Method adds a new pinned address for this Passenger
  void add_pinned_address(Address *new_address) {
    pinned_addresses.push_back(new_address);
  }

  // Method returns pinned addresses of Passenger
  std::vector<Address *> get_pinned_addresses() { return pinned_addresses; }

  // Method adds new payment method for Passenger
  void add_payment_method(payment::Payment *new_method) {
    payment_methods.push_back(new_method);
  }

  // Method returns payment methods of Passenger
  std::vector<payment::Payment *> get_payment_methods() {
    return payment_methods;
  }

  // Method allows to pay with a given payment method
  void pay(int index_of_payment_method, float price) {
    if (payment_methods.size() > index_of_payment_method) {
      payment_methods[index_of_payment_method]->pay(price);
    }
  }

  // Method returns a tuple,
  // which will be overwritten by Driver who will pick this Ride
  std::tuple<Order *, Passenger *, driver::Driver *, int> create_order(
      Address _from, Address _to, car::CarType _type, int payment_idx) {
    auto new_order = new Order(_from, _to, _type);

    bool has_enough_money =
        payment_methods[payment_idx]->get_money() >= new_order->get_price();

    // If we do not have enough money for ride, we skip Order, by subsututing
    // null pointer
    if (!has_enough_money)
      return (std::make_tuple(nullptr, this, nullptr, payment_idx));

    // Everything was okay, we can afford this Ride at least from one payment
    // method
    return (std::make_tuple(new Order(_from, _to, _type), this, nullptr,
                            payment_idx));
  }
};

#endif
