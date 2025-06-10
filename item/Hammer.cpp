#include "Hammer.h"
#include "../game/Game.h"

void Hammer::use(Position pos) {
    Maze& maze{ Game::maze() };

    if (maze.cellAt(pos) == Cell::wall && maze.isWithinBounds(pos)) {
        maze.updateCell(pos, Cell::passage);
    }
}