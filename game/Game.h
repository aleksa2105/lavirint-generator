#pragma once

#include "Helper.h"
#include "../common/Direction.h"
#include "../entity/Robot.h"
#include "../entity/Minotaur.h"
#include "../io/CLI.h"
#include "../maze/Maze.h"
#include "../maze_generator/MazeGenerator.h"
#include "../utils/Random.h"
#include "../item/Item.h"


class Game {
public:
    Game(int argc, char* argv[]);

    // main game loop
    void run();

    bool running() const;

    void exit();

    void robotTurn();

    void minotaurTurn();

    /* access methods */
    static Maze& maze() { return s_maze; }
    static Robot& robot() { return s_robot; }
    static Minotaur& minotaur() { return s_minotaur; }

private:
    void init();

private:
    MazeGenerator m_mazeGenerator;
    static Maze s_maze;
    static Robot s_robot;
    static Minotaur s_minotaur;
};