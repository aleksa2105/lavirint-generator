cmake_minimum_required(VERSION 3.10.0)
project(maze VERSION 0.1.0 LANGUAGES C CXX)

add_executable(maze main.cpp
    common/Cell.h
    common/Direction.h
    common/Position.h

    entity/Entity.h
    entity/Robot.h
    entity/Robot.cpp
    entity/Minotaur.cpp
    entity/Minotaur.h

    game/Game.h
    game/Game.cpp
    game/GameState.h

    io/CLI.h
    io/CLI.cpp

    maze/Maze.h
    maze/Maze.cpp

    maze_generator/MazeGenerator.h
    maze_generator/MazeGenerator.cpp
    maze_generator/MazeData.h
    maze_generator/Settings.h


    utils/Color.h
    utils/Random.h
    utils/Utils.h
)

