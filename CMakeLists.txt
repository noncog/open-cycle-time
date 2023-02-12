cmake_minimum_required(VERSION 3.24)
project(open-cycle-time
        VERSION 0.0.1
        DESCRIPTION "A cross-platform video analysis tool for generating cycle times of manufacturing processes."
        HOMEPAGE_URL "https://github.com/noncog/open-cycle-time"
        LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_EXTENSIONS OFF)

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
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v0.1.36
        GIT_PROGRESS TRUE)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.89.2
        GIT_PROGRESS TRUE)

FetchContent_Declare(
        implot
        GIT_REPOSITORY https://github.com/epezent/implot.git
        GIT_TAG d87512353495e7760e7fda7566a05beef7627d8f
        GIT_PROGRESS TRUE)

set(PROJECT_DEPENDENCIES
        glfw
        glad
        imgui
        implot)

FetchContent_MakeAvailable(${PROJECT_DEPENDENCIES})

# notice we reuse the name from the FetchContent_Declare
add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp)

target_include_directories(imgui INTERFACE
        ${imgui_SOURCE_DIR})

add_library(implot STATIC
        ${implot_SOURCE_DIR}/implot.cpp
        ${implot_SOURCE_DIR}/implot_demo.cpp
        ${implot_SOURCE_DIR}/implot_items.cpp)

target_include_directories(implot PUBLIC
        ${implot_SOURCE_DIR}
        ${imgui_SOURCE_DIR})

set(PROJECT_SOURCES
        main.cpp
        src/open_cycle_time.cpp
        src/gui_context.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_DEPENDENCIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(CTest)
add_subdirectory(test)