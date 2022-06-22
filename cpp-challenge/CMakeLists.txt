cmake_minimum_required(VERSION 2.8)
project(BUGGY)

#add the executable
add_executable(BUGGY buggy.cxx)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


target_link_libraries(BUGGY pthread)
