cmake_minimum_required(VERSION 3.24)
project(open-cycle-time)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(open-cycle-time main.cpp)