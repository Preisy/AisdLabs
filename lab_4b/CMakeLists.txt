cmake_minimum_required(VERSION 3.20)
project(lab_4b)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)
include_directories(src)

add_executable(main main.cpp)
add_executable(startup startup.cpp)
add_executable(test test.cpp)
add_executable(timing timing.cpp)
