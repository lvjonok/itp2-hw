#include <string>

#ifndef ADDRESS_H
#define ADDRESS_H

class Address {
  std::string value;

 public:
  Address(std::string value) : value(value) {}
  Address() : value("") {}
  // function returns string with address class
  std::string serialize() {
    return value;
  }
};

#endif
