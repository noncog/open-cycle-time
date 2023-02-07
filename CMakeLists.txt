cmake_minimum_required(VERSION 3.24)
project(open-cycle-time
        VERSION 0.0.1
        DESCRIPTION "A cross-platform video analysis tool for generating cycle times of manufacturing processes."
        HOMEPAGE_URL "https://github.com/noncog/open-cycle-time"
        LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(open-cycle-time main.cpp)