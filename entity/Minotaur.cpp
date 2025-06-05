#include "Minotaur.h"

bool Minotaur::canMoveTo(Maze& maze, Position newPos) {
    if (maze.isValidMove(newPos)) {
        return true;
    }

    return false;
}