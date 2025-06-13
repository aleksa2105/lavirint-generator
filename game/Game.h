#pragma once

#include "../entity/Robot.h"
#include "../entity/Minotaur.h"
#include "../maze/Maze.h"


namespace Game {
    void init(int argc, char* argv[]);

    // main game loop
    void run();

    bool running();

    void exit();

    void robotTurn();

    void minotaurTurn();

    /* Static variables available everywhere */
    extern Maze s_maze;
    extern Robot s_robot;
    extern Minotaur s_minotaur;
};