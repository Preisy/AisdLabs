cmake_minimum_required(VERSION 3.16.3)
project(lab_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(table)
include_directories(lib)

add_executable(startup
        startup.cpp
        table/KeySpaces/KeySpace1/KeySpace1.h
        table/KeySpaces/Node.h
        table/CompositeKey.h
        table/KeySpaces/KeySpace1/Key1.h table/KeySpaces/IKey.h lib/ActionResult.h lib/Pair.h table/Item.h src/controller/TableController.h)

add_executable(lab_3
        main.cpp
        table/KeySpaces/KeySpace1/KeySpace1.h
        table/KeySpaces/Node.h
        table/CompositeKey.h
        table/KeySpaces/KeySpace1/Key1.h table/KeySpaces/IKey.h lib/ActionResult.h lib/Pair.h table/Item.h)

add_executable(test test.cpp)
add_executable(test2 test2.cpp)
add_executable(iterator1 iterators/iterator1.cpp)
add_executable(iterator2 iterators/iterator2.cpp)