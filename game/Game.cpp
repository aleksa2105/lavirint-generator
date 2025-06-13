#include "Game.h"
#include "../utils/Random.h"
#include "../io/FileManager.h"
#include <iostream>
#include "../item/Sword.h"
#include "../item/Shield.h"
#include "../io/FileManager.h"

Game::Game(int argc, char* argv[])
    : m_mazeGenerator{ Settings{handleArguments(argc, argv)} }
{
    init();
}

/* Initialize static members */
Maze Game::s_maze;
Robot Game::s_robot;
Minotaur Game::s_minotaur;

/* Setup maze */
void Game::init() {
    s_maze.setData(m_mazeGenerator.generate());
    s_robot.setPosition(Helper::getRobotPosition(s_maze.enterPos()));
    s_minotaur.setPosition(Helper::getMinotaurPosition(s_maze.numRows(), s_maze.numCols()));

    s_maze.updateCell(s_robot.pos(), Cell::robot);
    s_maze.updateCell(s_minotaur.pos(), Cell::minotaur);
}

void Game::run() {
    while (running()) {
        CLI::display(s_maze);

        robotTurn();
        if (!running())
            exit();
        minotaurTurn();
    }
    exit();
}

bool Game::running() const {
    return s_robot.isAlive() && s_robot.pos() != s_maze.exitPos();
}

void Game::exit() {
    CLI::display(s_maze);

    FileManager fileManager{ "output.txt" };

    // save to file
    fileManager.save(s_maze);
    fileManager.save("GENERATION-TIME: " + std::to_string(s_maze.generationTime()));

    std::exit(EXIT_SUCCESS);
}

void Game::robotTurn() {
    char userInput{ CLI::getUserInput() };

    if (tolower(userInput) == 'q') { exit(); }

    std::optional<Direction> dir{ directionFromChar(userInput) };

    if (dir) {
        Position newPos{ s_robot.pos() + dir.value() };
        // before moving let item do its job
        s_robot.useItem(newPos);
        s_robot.move(newPos);
    }
    else {
        std::cout << "\nInvalid input\n";
    }
}

void Game::minotaurTurn() {

    if (s_minotaur.isKO()) {
        s_minotaur.reduceKODuration();
        return;
    }
    if (!s_minotaur.isAlive() || !s_robot.isAlive()) {
        return;
    }

    int minotaurX{ s_minotaur.pos().x };
    int minotaurY{ s_minotaur.pos().y };
    int robotX{ s_robot.pos().x };
    int robotY{ s_robot.pos().y };

    // try to kill robot if near
    if ((abs(minotaurX - robotX) == 1 && abs(minotaurY - robotY) == 0) || (abs(minotaurX - robotX) == 0 && abs(minotaurY - robotY) == 1)) {
        s_robot.defend();

        if (!s_minotaur.isAlive() || s_minotaur.isKO())
            // robot defended successfully
            return;

        // robot failed to defend. update maze cells and return
        s_maze.updateCell(s_robot.pos(), Cell::minotaur);
        s_maze.updateCell(s_minotaur.pos(), Cell::passage);
        return;
    }

    // add all available directions to vector and select one randomly
    std::vector<Direction> availableDir{};
    Position curPos{ s_minotaur.pos() };
    if (s_minotaur.canMoveTo(curPos + Direction{ 0, -1 })) availableDir.emplace_back(0, -1); // north
    if (s_minotaur.canMoveTo(curPos + Direction{ 0, 1 })) availableDir.emplace_back(0, 1); // south
    if (s_minotaur.canMoveTo(curPos + Direction{ -1, 0 })) availableDir.emplace_back(-1, 0); // west
    if (s_minotaur.canMoveTo(curPos + Direction{ 1, 0 })) availableDir.emplace_back(1, 0); // east

    // randomly select direction
    int randIdx = Random::get(0, static_cast<int>(availableDir.size()) - 1);
    Direction dir = availableDir[randIdx];
    Position newPos{ curPos + dir };

    // update maze and minotaur data
    s_maze.updateCells(curPos, newPos);
    s_minotaur.setPosition(newPos);
}

