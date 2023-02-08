cmake_minimum_required(VERSION 3.24)
project(open-cycle-time
        VERSION 0.0.1
        DESCRIPTION "A cross-platform video analysis tool for generating cycle times of manufacturing processes."
        HOMEPAGE_URL "https://github.com/noncog/open-cycle-time"
        LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
        GIT_PROGRESS TRUE)

FetchContent_Declare(
         glad
         GIT_REPOSITORY https://github.com/Dav1dde/glad
         GIT_TAG v0.1.36
        GIT_PROGRESS TRUE)

set(PROJECT_DEPENDENCIES
        glfw
        glad)

FetchContent_MakeAvailable(${PROJECT_DEPENDENCIES})

set(PROJECT_SOURCES
        main.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_DEPENDENCIES})
