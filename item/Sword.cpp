#include "Sword.h"
#include "../game/Game.h"

void Sword::use(Position pos) {
    Maze& maze{ Game::s_maze };

    if (maze.cellAt(pos) == Cell::minotaur) {
        Minotaur& minotaur{ Game::s_minotaur };
        minotaur.kill();
        maze.updateCell(pos, Cell::passage);
        std::cout << "\nYou have killed minotaur. Try to find the exit...\n";
    }
}