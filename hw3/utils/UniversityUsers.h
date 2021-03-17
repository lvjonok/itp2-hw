#include <utility>

#include "User.h"
#include "Rooms.h"

#ifndef ITP2_HW_UNIVERSITYUSERS_H
#define ITP2_HW_UNIVERSITYUSERS_H

class Student : public User {
    // real property of student is having his group_id, like "BS20-03"
public:
    Student(std::string name, std::string surname, std::string group_id) : User(std::move(name), std::move(surname),
                                                                                AccessLevel::yellow) {
        this->property = std::move(group_id);
    }
};


class Professor : public User {
    // real property of professor is his/her position in university labs
public:
    Professor(std::string name, std::string surname, std::string title) : User(std::move(name), std::move(surname),
                                                                               AccessLevel::yellow) {
        this->property = std::move(title);
    }
};

class LabEmployee : public User {
    // real property of lab employee is his/her area_of_interest which is pretty much the same as the name of lab
public:
    LabEmployee(std::string name, std::string surname, std::string area) : User(std::move(name), std::move(surname),
                                                                                AccessLevel::green) {
        this->property = std::move(area);
    }
};

class Director : public User {
    // real property of director is his last work name
public:
    Director(std::string name, std::string surname, std::string work) : User(std::move(name), std::move(surname),
                                                                             AccessLevel::yellow) {
        this->property = std::move(work);
    }
};

class Admin : public User {
    // real property of any admin in our world is his nickname which he uses for games :)
public:
    Admin(std::string name, std::string surname, std::string nickname) : User(std::move(name), std::move(surname),
                                                                              AccessLevel::red) {
        this->property = std::move(nickname);
    }

    std::vector<std::string *> get_actions() override {
        auto common_res = User::get_actions();
        common_res.emplace_back(new std::string("grant access"));
        common_res.emplace_back(new std::string("toggle emergency"));
        return common_res;
    }

    bool is_admin() override {
        return true;
    }

    bool grant_access(User *user, Room *room) {
        if (room->access(user)) {
            // already have an access
            return false;
        } else {
            // in general lvl of access should be at least equal to lvl of room
            user->add_level(room->get_level());
            if (room->is_special()) room->add_user(user);
            return true;
        }
    }
    // method available only for admin, to open all passed rooms in case of emergency
    bool enable_emergency(const std::vector<Room*> &rooms) {
        for (auto room : rooms) {
            room->toggle_emergency(this);
        }
    }
};

#endif //ITP2_HW_UNIVERSITYUSERS_H
