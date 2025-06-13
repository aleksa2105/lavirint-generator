#include "Hammer.h"
#include "../game/Game.h"

void Hammer::use(Position pos) {
    Maze& maze{ Game::s_maze };

    if (maze.cellAt(pos) == Cell::wall && maze.isWithinBounds(pos)) {
        // destroy the wall
        maze.updateCell(pos, Cell::passage);
    }
}