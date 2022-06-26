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



# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests test/tests.cpp)
target_link_libraries(runTests 
    ${GTEST_LIBRARIES}
    buggy_lib
    pthread
    )


# Copy file
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test
         DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
