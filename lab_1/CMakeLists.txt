cmake_minimum_required(VERSION 3.16)
project(untitled C)

set(CMAKE_C_STANDARD 99)

include_directories(src)

add_executable(main main.c src/readMatrix.c src/printMatrix.c src/processMatrix.c src/Matrix.c)
