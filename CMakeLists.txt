cmake_minimum_required(VERSION 3.10.0)
project(maze VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(maze_generator)

add_executable(maze main.cpp
    entity/Robot.cpp
    entity/Minotaur.cpp
    game/Game.cpp
    io/CLI.cpp
    io/FileManager.cpp
    item/Item.cpp
    item/Fog.cpp
    item/Sword.cpp
    item/Hammer.cpp
    item/Shield.cpp
    maze/Maze.cpp
)

target_link_libraries(maze PUBLIC maze_generator)

