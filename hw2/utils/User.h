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
public:
    User(std::string name, std::string surname, AccessLevel level) {
        this->name = std::move(name);
        this->surname = std::move(surname);
        this->level = level;
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
    friend std::ostream& operator<< ( std::ostream& os, const User& user );
};

std::ostream& operator<< ( std::ostream& os, const User& user ) {
    os << user.name << " " << user.surname << " " << user.level;

    return os;
}

#endif //ITP2_HW_USER_H
