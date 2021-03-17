#include "AccessLevels.h"
#include "User.h"
#include <string>
#include <utility>
#include "vector"

#ifndef ITP2_HW_ROOMS_H
#define ITP2_HW_ROOMS_H

class Room
{
protected:
    AccessLevel level;
    bool special = false;
    // In case of emergency, all rooms will be opened
    bool emergency = false;
    std::string id;
    std::string type;

public:
    Room(std::string id, AccessLevel lvl, std::string type) : id(id), level(lvl), type(type) {}

    // method toogles emergency button, available only for admin access
    void toggle_emergency(User *user)
    {
        if (user->is_admin())
            emergency = !emergency;
    }

    std::string get_type() const
    {
        return this->type;
    }

    std::string get_id() const
    {
        return this->id;
    }

    AccessLevel get_level() const
    {
        return this->level;
    }

    // by default each room is NOT special, means it doesn't have granted_users list
    virtual bool is_special() const
    {
        return this->special;
    }

    // default method for granting access is false because it doesn't depend on granted_users list
    virtual bool add_user(User *user)
    {
        return false;
    }

    virtual bool access(User *user)
    {
        // for hw3 new situation for granting access is emergency situation
        if (this->emergency)
            return true;
        return this->level <= user->get_level();
    }

    friend std::ostream &operator<<(std::ostream &os, const User &user);
};

std::ostream &operator<<(std::ostream &os, const Room &room)
{
    os << room.get_type() << " ||| " << room.get_id() << " " << room.get_level();
    return os;
}

// class for study room which can be accessed by everyone with level higher or equal than no_level
class ClassRoom : public Room
{
public:
    ClassRoom(std::string id) : Room(std::move(id), AccessLevel::no_level, "ClassRoom") {}
    // we need to override default access function to prohibit Guests access to this room (no level is lower than blue)
    bool access(User *user) override
    {
        // for hw3 new situation for granting access is emergency situation
        if (this->emergency)
            return true;

        // prohibiting access
        if (user->get_level() == AccessLevel::blue)
            return false;

        return true;
    }
};

// class for lecture room which can be accesses by everyone with level higher or equal than green
class LectureRoom : public Room
{
public:
    LectureRoom(std::string id) : Room(std::move(id), AccessLevel::green, "LectureRoom") {}
    // overriding function of access for blue users
    bool access(User *user) override
    {
        // for hw3 new situation for granting access is emergency situation
        if (this->emergency)
            return true;
        // in hw3 lecture room can be accessed by people with blue level of access
        return (user->get_level() == AccessLevel::blue) || this->level <= user->get_level();
    }
};

// class for conference room which can be accesses by everyone with level higher or equal than yellow
class ConferenceRoom : public Room
{
public:
    ConferenceRoom(std::string id) : Room(std::move(id), AccessLevel::yellow, "ConferenceRoom") {}
    // overriding function of access for blue users
    bool access(User *user) override
    {
        // for hw3 new situation for granting access is emergency situation
        if (this->emergency)
            return true;
        // in hw3 ConferenceRoom can be accessed by people with yellow or higher
        // or with people with blue level of access if Room id starts with '1' (on the first floor)
        if (user->get_level() == AccessLevel::blue && this->get_id()[0] == '1')
        {
            return true;
        }
        else
        {
            // usual condition
            return this->level <= user->get_level();
        }
    }
};

// class for lab cabinet which can be accessed only by granted_users with green or higher level of access
class LabCabinet : public Room
{
private:
    // we need to specify this list because not everyone with green level of access can access laboratory
    std::vector<User *> granted_users;

public:
    LabCabinet(std::string id, std::vector<User *> users) : Room(std::move(id), AccessLevel::green, "LabCabinet")
    {
        Room::special = true;
        this->granted_users = std::move(users);
    }

    // Overriding method for access because user should be in granted_users list
    bool access(User *user) override
    {
        // for hw3 new situation for granting access is emergency situation
        if (this->emergency)
            return true;
        if (user->is_admin())
            return true;
        // we look through all granted users and in case of match give access
        for (auto granted_user : this->granted_users)
        {
            if (user == granted_user)
                return true;
        }
        return false;
    }

    bool add_user(User *user) override
    {
        for (auto granted_user : this->granted_users)
        {
            if (user == granted_user)
                // we return false because user is already added
                return false;
        }
        this->granted_users.push_back(user);
        return true;
    }
};

// class for cabinet which can be accesed only by owner or by granted_users with yellow or higher level of access
class Cabinet : public Room
{
private:
    // contains the user who owns the cabinet
    User *owner;
    // contains users who were granted an access
    std::vector<User *> granted_users;

public:
    Cabinet(std::string id, User *owner) : Room(std::move(id), AccessLevel::yellow, "Cabinet")
    {
        this->owner = owner;
        Room::special = true;
    }

    // Overriding method for access because user should be in granted_users list
    bool access(User *user) override
    {
        // for hw3 new situation for granting access is emergency situation
        if (this->emergency)
            return true;
        // base case for granting an access is being the owner of this cabinet
        if (user == owner || user->is_admin())
            return true;
        // we look through all granted users and in case of match give access
        for (auto granted_user : this->granted_users)
        {
            if (user == granted_user)
                return true;
        }
        return false;
    }

    bool add_user(User *user) override
    {
        for (auto granted_user : this->granted_users)
        {
            if (user == granted_user)
                // we return false because user is already added
                return false;
        }
        this->granted_users.push_back(user);
        return true;
    }
};

#endif //ITP2_HW_ROOMS_H