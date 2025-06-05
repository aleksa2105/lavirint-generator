#pragma once
#include "../maze_generator/MazeGenerator.h"
#include "../maze/Maze.h"
#include "../entity/Robot.h"
#include "../entity/Minotaur.h"
#include "GameState.h"
#include "../common/Direction.h"
#include "../io/CLI.h"
#include "../utils/Random.h"


class Game {
public:
    Game(int argc, char* argv[]);

    // main game loop
    void run();

    void exit();

    // return direction if valid input
    std::optional<Direction> directionFromInput(char c);

public: /* Helper functions for setting up game */

    // being said that robot is placed one cell bellow entrance, we need enter position
    static Position getRobotPosition(Position enterPos) { return { enterPos.x, enterPos.y + 1 }; }

    // we need size of maze to randomly place minotaur
    static Position getMinotaurPosition(int numRows, int numCols) {
        int x{ Random::get(1, numCols - 2) }; // pick x in safe bounds
        int y{ Random::get(numRows / 2, numRows - 2) }; // we will place minotaur on lower half of maze
        return Position{ x,y };
    }

private:
    GameState m_state;
    MazeGenerator m_mazeGenerator;
    Maze m_maze;
    Robot m_robot;
    Minotaur m_minotaur;
};