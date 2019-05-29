cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(draw_circle)

add_executable(draw_circle src/draw_circle.cpp)
target_link_libraries(draw_circle
                      glut
                      GL
                      GLU
                      GLEW)
