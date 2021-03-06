cmake_minimum_required(VERSION 3.17)
project(hw2)

set(CMAKE_CXX_STANDARD 17)

include_directories(utils)

add_executable(hw2
        utils/AccessLevels.h
        utils/Rooms.h
        utils/UniversityUsers.h
        utils/User.h
        main.cpp)
