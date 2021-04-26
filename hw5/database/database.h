// Code helps to work with created database
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "../utils/Driver.h"
#include "../utils/Order.h"
#include "../utils/Passenger.h"
#include "../utils/Ride.h"

#ifndef DATABASE_H
#define DATABASE_H

namespace database {

// Method parses line by line each object from given file, and given object as
// template
template <class T>
std::vector<T*> get(std::string filename) {
  std::ifstream cin;
  cin.open(filename);

  std::vector<T*> objects;
  for (std::string line; getline(cin, line);) {
    if (line.size() != 0) objects.push_back(new T(line));
  }
  return objects;
}

// Method uploads given vector to database with given filename. Object to be
// loaded into database should contain method serialize(), which represents its
// as string
template <class T>
void set(std::string filename, std::vector<T*> objects) {
  std::ofstream database;
  database.open(filename);

  for (auto object : objects) {
    database << object->serialize() << std::endl;
  }

  database.close();
}

// parse Ride
std::vector<Ride*> get_rides_pending() {
  return get<Ride>("database/rides_pending.csv");
}
std::vector<Ride*> get_rides_complete() {
  return get<Ride>("database/rides_completed.csv");
}

// Method returns vector with all drivers from database
std::vector<driver::Driver*> get_drivers() {
  return get<driver::Driver>("database/drivers.csv");
}

// Method returns vector with all passengers from database
std::vector<Passenger*> get_passengers() {
  return get<Passenger>("database/passengers.csv");
}

void load_rides_pending(std::vector<Ride*> _ride) {
  set<Ride>("database/rides_pending.csv", _ride);
}
void load_rides_completed(std::vector<Ride*> _ride) {
  set<Ride>("database/rides_completed.csv", _ride);
}

// Method updates database entries with all drivers from vector
void load_drivers(std::vector<driver::Driver*> drivers) {
  set<driver::Driver>("database/drivers.csv", drivers);
}

// Method update Database with all passengers
void load_passengers(std::vector<Passenger*> passengers) {
  set<Passenger>("database/passengers.csv", passengers);
}
};  // namespace database

#endif