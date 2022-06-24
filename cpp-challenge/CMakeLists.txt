cmake_minimum_required(VERSION 2.8)
project(app)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(buggy/)

add_executable(app main.cpp)

target_link_libraries(app
    PUBLIC
        buggy_lib
        pthread
        )
