cmake_minimum_required(VERSION 3.13)

project(maze_generator)

add_library(maze_generator STATIC src/MazeGenerator.cpp)

target_include_directories(maze_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)