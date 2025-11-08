cmake_minimum_required(VERSION 4.0)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

# Tell CMake to find libpqxx that vcpkg installs
find_package(libpqxx CONFIG REQUIRED)

add_executable(untitled main.cpp
        "view.h"
        view.cpp
        "manageStudentControl.h"
        manageStudentControl.cpp
        db.h
        db.cpp)
target_link_libraries(untitled PRIVATE libpqxx::pqxx)