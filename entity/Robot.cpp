#include "Robot.h"
#include <iostream>


bool Robot::canMoveTo(Maze& maze, Position newPos) {
    if (newPos == maze.exitPos() || maze.isValidMove(newPos)) {
        return true;
    }

    return false;
}