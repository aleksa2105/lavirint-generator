cmake_minimum_required(VERSION 3.10.0)
project(maze VERSION 0.1.0 LANGUAGES C CXX)

add_executable(maze main.cpp
    common/Cell.h
    common/Direction.h
    common/Position.h

    maze_generator/MazeGenerator.h
    maze_generator/MazeGenerator.cpp
    maze_generator/Settings.h

    maze/Maze.h
    maze/Maze.cpp

    utils/Color.h
    utils/Random.h
    utils/Utils.h
)

