cmake_minimum_required(VERSION 3.22)
project(CWonNewGroup)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(CWonNewGroup
        include/Group.hpp
        include/Menu.hpp
        include/Stream.hpp
        include/Student.hpp
        Group.cpp
        main.cpp
        Menu.cpp
        Stream.cpp
        Student.cpp
        t2.txt
        test.txt)
