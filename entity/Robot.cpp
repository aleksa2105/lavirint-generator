#include <iostream>
#include "Robot.h"
#include "../item/Hammer.h"
#include "../item/Sword.h"
#include "../item/Fog.h"
#include "../item/Shield.h"
#include "../game/Game.h"


bool Robot::canMoveTo(Position newPos) {
    if (newPos == Game::maze().exitPos() || Game::maze().isValidMove(newPos)) {
        return true;
    }
    return false;
}

void Robot::useItem(Position pos) {
    if (m_activeItem) {
        if (m_activeItem->isBroken()) {
            m_activeItem = nullptr;
        }
        else {
            m_activeItem->use(pos);
            m_activeItem->reduceDuration();
            m_activeItem->isBroken() ? std::cout << "\nYour item has broken.\n" : std::cout << "\n{Active item: " << *m_activeItem << "}\n";
        }
    }
}