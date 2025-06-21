#include <iostream>
#include "Robot.h"
#include "../item/Hammer.h"
#include "../item/Sword.h"
#include "../item/Fog.h"
#include "../item/Shield.h"
#include "../game/Game.h"


bool Robot::canMoveTo(Lib::Position newPos) {
    if (newPos == Game::s_maze.exitPos() || Game::s_maze.isWalkable(newPos)) {
        return true;
    }
    return false;
}

void Robot::useItem(Lib::Position pos) {
    if (m_activeItem) {
        if (m_activeItem->isBroken()) {
            m_activeItem = nullptr;
        }
        else {
            m_activeItem->use(pos);
            m_activeItem->reduceDuration(); // after each use, reduce item's duration
            m_activeItem->isBroken() ? std::cout << "\nYour item has broken.\n" : std::cout << "\n{Active item: " << *m_activeItem << "}\n";
        }
    }
}

void Robot::pickupItem(std::unique_ptr<Item> item) {
    m_activeItem = std::move(item); // take ownership of passed item
    std::cout << "\nYou have picked up: " << m_activeItem->getStr() << '\n';
}

void Robot::move(Lib::Position newPos) {
    Maze& maze{ Game::s_maze };
    Minotaur& minotaur{ Game::s_minotaur };

    if (canMoveTo(newPos)) {
        Lib::Cell cell{ maze.cellAt(newPos) };

        // encounter item
        if (cell == Lib::Cell::item) {
            pickupItem(getRandomItem());
        }
        // found exit
        else if (cell == Lib::Cell::exit) {
            std::cout << "\nYou have won!!\n";
        }
        // encounter minotaur when he is ready to attack
        // since item is used before robot's move but minotaur is still alive,
        // it means that robot didn't have proper item at proper time
        else if (cell == Lib::Cell::minotaur && !minotaur.isKO() && minotaur.isAlive()) {
            kill();
            maze.updateCell(pos(), Lib::Cell::passage);
            std::cout << "\nYou have died. GG\n";
            return;
        }
        // encounter minotaur when he is knocked out
        else if (cell == Lib::Cell::minotaur && minotaur.isKO()) {
            return; // don't move the robot, just return
        }

        // update maze cells and robot's position
        maze.swapCells(pos(), newPos);
        setPosition(newPos);
        return;
    }
}

void Robot::defend() {
    Minotaur& minotaur{ Game::s_minotaur };
    if (m_activeItem) {
        m_activeItem->use(minotaur.pos());
        if (!minotaur.isAlive() || minotaur.isKO()) {
            return; // return if robot defended successfully
        }
    }

    kill(); // robot failed to defend
    std::cout << "\nYou have died against minotaur's attack.\n";
    std::cout << "Game's over...\n";
}