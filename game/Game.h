#pragma once

#include "../entity/Robot.h"
#include "../entity/Minotaur.h"
#include "../maze/Maze.h"


namespace Game {

    // generate maze and initialize entities
    void init(int argc, char* argv[]);

    // main game loop
    void run();

    bool running();

    // save final state of the maze to a file and close the application
    void exit();

    void robotTurn();

    void minotaurTurn();

    /* Static variables available everywhere */
    extern Maze s_maze;
    extern Robot s_robot;
    extern Minotaur s_minotaur;
};