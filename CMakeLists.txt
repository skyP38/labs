cmake_minimum_required(VERSION 3.27)
project(l1)

set(CMAKE_CXX_STANDARD 23)

add_library(input 1/input.h 1/input.cpp)
add_library(func 1/func.h 1/func.cpp)

link_libraries(input func)

add_executable(l1 1/main.cpp)
#add_executable(l1 tests.cpp)
