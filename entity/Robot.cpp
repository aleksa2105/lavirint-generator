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

void Robot::pickupItem(std::unique_ptr<Item> item) {
    m_activeItem = std::move(item);
    std::cout << "\nYou have picked up: " << m_activeItem->getStr() << '\n';
}

void Robot::move(Position newPos) {
    Maze& maze{ Game::maze() };
    Minotaur& minotaur{ Game::minotaur() };

    if (canMoveTo(newPos)) {
        Cell cell{ maze.cellAt(newPos) };

        // encounter item
        if (cell == Cell::item) {
            pickupItem(getRandomItem());
        }
        // encounter minotaur when he is ready to attack
        else if (cell == Cell::minotaur && !minotaur.isKO() && minotaur.isAlive()) {
            kill();
            maze.updateCell(pos(), Cell::passage);
            std::cout << "\nYou have died. GG\n";
            return;
        }
        // encounter minotaur when he is knocked out
        else if (cell == Cell::minotaur && minotaur.isKO()) {
            return; // don't move the robot, just return
        }
        // found exit
        else if (cell == Cell::exit) {
            std::cout << "\nYou have won!!\n";
        }

        maze.updateCells(pos(), newPos);
        setPosition(newPos);
        return;
    }
}

void Robot::defend() {
    Minotaur& minotaur{ Game::minotaur() };
    if (m_activeItem) {
        m_activeItem->use(minotaur.pos());
        if (!minotaur.isAlive() || minotaur.isKO()) {
            return;
        }
    }
    kill();
    std::cout << "\nYou have died against minotaur's attack.\n";
    std::cout << "Game's over...\n";
}