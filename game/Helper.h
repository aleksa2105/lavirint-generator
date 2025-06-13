#pragma once
#include "../common/Position.h"
#include "../utils/Random.h"


namespace Helper { /* Helper functions for setting up the game */

    // position robot one cell below entrance 
    inline Position getRobotPosition(Position enterPos) { return { enterPos.x, enterPos.y + 1 }; }

    // randomly place minotaur in lower half of the maze
    inline Position getMinotaurPosition(int numRows, int numCols) {
        int x{ Random::get(1, numCols - 2) }; // pick x in safe bounds
        int y{ Random::get(numRows / 2, numRows - 2) };
        return Position{ x,y };
    }
}
