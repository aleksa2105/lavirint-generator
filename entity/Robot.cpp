#include "Robot.h"
#include <iostream>


bool Robot::canMoveTo(Maze& maze, Position newPos) {
    if (newPos == maze.exitPos() || maze.isValidMove(newPos)) {
        return true;
    }

    return false;
}

std::string_view Robot::activeItemStr() const {
    if (m_activeItem) {
        return m_activeItem->getStr();
    }
    return "No active item";
}