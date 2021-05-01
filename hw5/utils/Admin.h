#include <string>
#include <vector>

#include "Permission.h"

#ifndef ADMIN_H
#define ADMIN_H
namespace admin {

class Admin {
  std::string name;

 public:
  Admin(std::string _name) : name(_name) {}
  std::string get_name() { return name; }
  std::string serialize() { return get_name(); }
  // Constuctor for new permission which will overwrite current for given
  // user_name
  Permission* set_permission(std::string user_name, int code) {
    return new Permission(user_name, code);
  }
};

/**
 * @brief Login method to choose required admin from the list
 *
 * @param admins
 * @param idx
 * @return Admin*
 */
Admin* login(std::vector<Admin*> admins, int idx) { return admins[idx]; }

}  // namespace admin

#endif