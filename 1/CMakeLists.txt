cmake_minimum_required(VERSION 3.27)
project(laba1)

set(CMAKE_CXX_STANDARD 23)

add_library(input input.h input.cpp)
add_library(func func.h func.cpp)

link_libraries(input func)

add_executable(laba1 main.cpp)
#add_executable(l1 tests.cpp)
