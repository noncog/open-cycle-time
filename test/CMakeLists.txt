cmake_minimum_required(VERSION 3.24)
project(open-cycle-time-test LANGUAGES CXX C)

Include(FetchContent)
FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.9
        GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(doctest)

set(TEST_SOURCES
        tests.cpp)

add_executable(${PROJECT_NAME} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE doctest)

list(APPEND CMAKE_MODULE_PATH ${doctest_SOURCE_DIR}/scripts/cmake/)
include(doctest) # note: this doctest refers to the cmake module to enable the following:
doctest_discover_tests(${PROJECT_NAME})