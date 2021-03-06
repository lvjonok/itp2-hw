#include <utility>

#include "User.h"
#include "Rooms.h"

#ifndef ITP2_HW_UNIVERSITYUSERS_H
#define ITP2_HW_UNIVERSITYUSERS_H

class Student : public User
{
private:
    // real property of student is having his group_id, like "BS20-03"
    std::string group_id;
public:
    Student(std::string name, std::string surname, std::string group_id) : User(std::move(name), std::move(surname), AccessLevel::yellow) {
        this->group_id = std::move(group_id);
    }
};


class Professor : public User
{
private:
    // real property of professor is his/her position in university labs
    std::string title;
public:
    Professor(std::string name, std::string surname, std::string title) : User(std::move(name), std::move(surname), AccessLevel::yellow) {
        this->title = std::move(title);
    }
};

class LabEmployee : public User
{
private:
    // real property of lab employee is his/her area_of_interest which is pretty much the same as the name of lab
    std::string area_of_interest;
public:
    LabEmployee(std::string name, std::string surname, std::string area) : User(std::move(name), std::move(surname), AccessLevel::green) {
        this->area_of_interest = std::move(area);
    }
};

class Director : public User
{
private:
    // real property of director is his last work name
    std::string previous_work;
public:
    Director(std::string name, std::string surname, std::string work) : User(std::move(name), std::move(surname), AccessLevel::yellow) {
        this->previous_work = std::move(work);
    }
};

class Admin : public User
{
private:
    // real property of any admin in our world is his nickname which he uses for games :)
    std::string nickname;
public:
    Admin(std::string name, std::string surname, std::string nickname) : User(std::move(name), std::move(surname), AccessLevel::red) {
        this->nickname = std::move(nickname);
    }
    bool is_admin() override {
        return true;
    }
    bool grant_access(User* user, Room* room) {
        if (room->access(user)) {
            // already have an access
            return true;
        } else {
            // in general lvl of access should be at least equal to lvl of room
            user->add_level(room->get_level());
            if (room->is_special()) room->add_user(user);
        }
    }
};

#endif //ITP2_HW_UNIVERSITYUSERS_H
