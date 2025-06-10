#include "Minotaur.h"
#include "../game/Game.h"

bool Minotaur::canMoveTo(Position newPos) {
    if (Game::maze().isValidMove(newPos)) {
        return true;
    }

    return false;
}
