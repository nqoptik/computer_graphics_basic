cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(recursive_tree)

add_executable(recursive_tree src/recursive_tree.cpp)
target_link_libraries(recursive_tree glut GL)
