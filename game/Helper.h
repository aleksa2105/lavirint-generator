#pragma once
#include "../common/Position.h"
#include "../utils/Random.h"


namespace Helper {

    /* Helper functions for setting up the game */

    // being said that robot is placed one cell bellow entrance, we pass the enter position
    inline Position getRobotPosition(Position enterPos) { return { enterPos.x, enterPos.y + 1 }; }

    // we need size of the maze to randomly place minotaur within maze bounds
    inline Position getMinotaurPosition(int numRows, int numCols) {
        int x{ Random::get(1, numCols - 2) }; // pick x in safe bounds
        int y{ Random::get(numRows / 2, numRows - 2) }; // we will place minotaur on lower half of maze
        return Position{ x,y };
    }
}
