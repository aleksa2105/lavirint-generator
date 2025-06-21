#include "Shield.h"
#include "../game/Game.h"

void Shield::use(Lib::Position pos) {
    Maze& maze{ Game::s_maze };

    if (maze.cellAt(pos) == Lib::Cell::minotaur) {
        Minotaur& minotaur{ Game::s_minotaur };
        minotaur.knockOut();
        std::cout << "\nYou have knocked down minotaur. Try to move away from him...\n";
    }
}