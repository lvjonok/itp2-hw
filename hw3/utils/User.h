#include <string>
#include <utility>
#include "AccessLevels.h"

#ifndef ITP2_HW_USER_H
#define ITP2_HW_USER_H

class User {
protected:
    AccessLevel level;
    std::string name;
    std::string surname;
    std::string type;
    std::string property = "";
public:
    User(std::string name, std::string surname, AccessLevel level, std::string type) {
        this->name = std::move(name);
        this->surname = std::move(surname);
        this->level = level;
        this->type = type;
    }

    AccessLevel get_level() {
        return this->level;
    }

    void add_level(AccessLevel new_lvl) {
        if (this->level < new_lvl) this->level = new_lvl;
    }

    virtual bool is_admin() {
        return false;
    }

    virtual std::string get_property() {
        return this->property;
    }

    std::string get_name_surname() {
        return this->name + " " + this->surname;
    }

    virtual std::vector<std::string *> get_actions() {
        return {
                new std::string("exit (stop simulation)"),
                new std::string("change user"),
                new std::string("access to certain room"),
                new std::string("get user name and surname"),
                new std::string("get user property"),
                new std::string("get user level")
        };
    }

    friend std::ostream &operator<<(std::ostream &os, const User &user);
};

std::ostream &operator<<(std::ostream &os, const User &user) {
    os << user.type << " ||| " <<  user.name << " " << user.surname << " | " << user.property << " | " << user.level;

    return os;
}

#endif //ITP2_HW_USER_H
