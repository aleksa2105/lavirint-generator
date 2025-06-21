#include "Minotaur.h"
#include "../game/Game.h"
#include "utils/Random.h"


bool Minotaur::canMoveTo(Lib::Position newPos) {
    if (Game::s_maze.isWalkable(newPos)) {
        return true;
    }

    return false;
}

void Minotaur::move() {
    Maze& maze{ Game::s_maze };
    Robot& robot{ Game::s_robot };

    // try to kill robot if near
    if ((abs(pos().x - robot.pos().x) == 1 && abs(pos().y - robot.pos().y) == 0) ||
        (abs(pos().x - robot.pos().x) == 0 && abs(pos().y - robot.pos().y) == 1)) {
        robot.defend();

        if (!isAlive() || isKO())
            // robot defended successfully
            return;

        // robot failed to defend. update maze cells and return
        maze.updateCell(robot.pos(), Lib::Cell::minotaur);
        maze.updateCell(pos(), Lib::Cell::passage);
        return;
    }

    // move randomly
    // add all available directions to vector and select one randomly
    std::vector<Lib::Direction> availableDir{};
    if (canMoveTo(pos() + Lib::Direction{ 0, -1 })) availableDir.emplace_back(0, -1); // north
    if (canMoveTo(pos() + Lib::Direction{ 0, 1 })) availableDir.emplace_back(0, 1); // south
    if (canMoveTo(pos() + Lib::Direction{ -1, 0 })) availableDir.emplace_back(-1, 0); // west
    if (canMoveTo(pos() + Lib::Direction{ 1, 0 })) availableDir.emplace_back(1, 0); // east

    // randomly select direction
    int randIdx = Random::get(0, static_cast<int>(availableDir.size()) - 1);
    Lib::Direction dir = availableDir[randIdx];
    Lib::Position newPos{ pos() + dir };

    // update maze and minotaur data
    maze.swapCells(pos(), newPos);
    setPosition(newPos);
}

void Minotaur::reduceKODuration() {
    std::cout << "\nMinotaur is knocked down for " << KODurationLeft << " more move(s)\n";
    --KODurationLeft;
}