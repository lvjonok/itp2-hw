#ifndef ITP2_HW_ACCESSLEVELS_H
#define ITP2_HW_ACCESSLEVELS_H

/*
Access levels:
no_level - ClassRoom,
green - LabCabinet, ClassRoom, LectureRoom
yellow - ClassRoom, LectureRoom, ConferenceRoom, dir/prof cabinet,
red - all rooms
*/

enum class AccessLevel : int {
    no_level = 0,
    green = 1,
    yellow = 2,
    red = 3
};

std::ostream &operator<<(std::ostream &os, const AccessLevel &a) {
    switch (a) {
        case AccessLevel::no_level:
            os << "no_level";
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
