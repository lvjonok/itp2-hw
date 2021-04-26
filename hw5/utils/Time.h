#include <string>

#ifndef TIME_H
#define TIME_H

// Class shows how much time was spend for particular ride
class Time {
  std::string date;

 public:
  // Constructor for Time class, date is in format seconds
  Time(std::string date) : date(date) {}
  Time() : date("") {}
  // Function returns string with Time class
  std::string serialize() { return date; }
};

#endif
