#include "Hammer.h"
#include "../game/Game.h"

void Hammer::use(Lib::Position pos) {
    Maze& maze{ Game::s_maze };

    if (maze.cellAt(pos) == Lib::Cell::wall && maze.isWithinBounds(pos)) {
        // destroy the wall
        maze.updateCell(pos, Lib::Cell::passage);
    }
}