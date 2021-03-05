/*
Access levels:
no_level - ClassRoom,
green - LabCabinet, ClassRoom, LectureRoom
yellow - ClassRoom, LectureRoom, ConferenceRoom, dir/prof cabinet,
red - all rooms
*/

enum class AccessLevel : int{
    no_level = 0,
    green = 1,
    yellow = 2,
    red = 3
};