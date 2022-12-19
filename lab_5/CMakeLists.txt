cmake_minimum_required(VERSION 3.16)
project(lab_5)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)
include_directories(src)
include_directories(digraph)

add_executable(main main.cpp)
add_executable(startup startup.cpp)
