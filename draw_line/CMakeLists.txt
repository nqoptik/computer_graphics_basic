cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(draw_line)

add_executable(draw_line src/draw_line.cpp)
target_link_libraries(draw_line glut GL)

