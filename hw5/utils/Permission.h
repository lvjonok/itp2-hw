#include <string>

#include "../database/parser.h"

#ifndef PERMISSION_H
#define PERMISSION_H

/**
 * @brief Class for exception for a driver to take a ride
 *
 */
class NoPermissionTakeRide {};

/**
 * @brief Class for exception for a passenger to add a ride
 *
 */
class NoPermissionAddRide {};

/**
 * @brief Class for exception for a passenger to ask for a special parking
 *
 */
class NoPermissionAskForSpecialParking {};
/**
 * @brief Class used for storing information about what users allowed to do or
 * not
 *
 * For every user 0 is no restrictions
 * For driver 1 means he restricted to take rides
 *
 * For passenger:
 * 0 - no restrictions
 * 1 - cannot add a ride
 * 2 - cannot ask for a special parking
 * 3 - cannot do anything
 *
 * Class stores the name of user and then maps it to the real user from database
 */
class Permission {
  std::string name;
  int code;

 public:
  Permission(std::string _name, int _code) : name(_name), code(_code) {}
  Permission(std::string raw) {
    auto tokens = parser::parse_string(raw, ',');
    name = tokens[0];
    code = stoi(tokens[1]);
  }
  std::string get_name() { return name; }
  int get_code() { return code; }
  /**
   * @brief Method returns serialized class Permission with format: name,code
   *
   * @return std::string
   */
  std::string serialize() { return name + "," + std::to_string(code); }
};

#endif