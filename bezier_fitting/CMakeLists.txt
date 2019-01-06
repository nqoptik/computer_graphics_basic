cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(bezier_fitting)

add_executable(bezier_fitting src/bezier_fitting.cpp)
target_link_libraries(bezier_fitting glut GL)
