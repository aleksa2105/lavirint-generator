#include "Sword.h"
#include "../game/Game.h"

void Sword::use(Lib::Position pos) {
    Maze& maze{ Game::s_maze };

    if (maze.cellAt(pos) == Lib::Cell::minotaur) {
        Minotaur& minotaur{ Game::s_minotaur };
        minotaur.kill();
        maze.updateCell(pos, Lib::Cell::passage);
        std::cout << "\nYou have killed minotaur. Try to find the exit...\n";
    }
}