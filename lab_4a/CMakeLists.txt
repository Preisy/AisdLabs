cmake_minimum_required(VERSION 3.16.3)
project(lab_4a)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib src)

add_executable(lab_4a getMapFromFile.cpp startup.cpp src/view/View.h src/controller/MapController.h)
add_executable(mainTest mainTest.cpp getMapFromFile.cpp src/view/View.h src/controller/MapController.h)
add_executable(task2ast task2ast.cpp)
add_executable(timing timing.cpp)
