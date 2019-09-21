cmake_minimum_required(VERSION 3.1)

project(recursive_tree)

## Compile as C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Compile with the highest warning level
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

## Declare a C++ executable
add_executable(recursive_tree src/recursive_tree.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(recursive_tree glut GL)
