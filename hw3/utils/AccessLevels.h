#ifndef ITP2_HW_ACCESSLEVELS_H
#define ITP2_HW_ACCESSLEVELS_H

/*
Access levels:
no_level - ClassRoom,
blue - LectureRoom, ConferenceRooms on the first floor
green - LabCabinet, ClassRoom, LectureRoom
yellow - ClassRoom, LectureRoom, ConferenceRoom, dir/prof cabinet,
red - all rooms
*/

enum class AccessLevel : int {
    no_level = 0,
    blue = 1,
    green = 2,
    yellow = 3,
    red = 4
};

std::ostream &operator<<(std::ostream &os, const AccessLevel &a) {
    switch (a) {
        case AccessLevel::no_level:
            os << "no_level";
            break;
        case AccessLevel::blue:
            os << "blue";
            break;
        case AccessLevel::green:
            os << "green";
            break;
        case AccessLevel::yellow:
            os << "yellow";
            break;
        case AccessLevel::red:
            os << "red";
            break;
    }

    return os;
}

#endif //ITP2_HW_ACCESSLEVELS_H
