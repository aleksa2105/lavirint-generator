#include "Game.h"
#include "../utils/Random.h"
#include "../io/FileManager.h"
#include <iostream>
#include "../item/Sword.h"
#include "../item/Shield.h"

Game::Game(int argc, char* argv[], std::string_view fileName)
    : m_mazeGenerator{ Settings{handleArguments(argc, argv)} }
    , m_fileManager{ fileName }
{
    init();
}

/* Initialize static members */
Maze Game::s_maze;
Robot Game::s_robot;
Minotaur Game::s_minotaur;

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
        minotaurTurn();
    }
    exit();
}

bool Game::running() const {
    return s_robot.isAlive() || s_robot.pos() != s_maze.exitPos();
}

void Game::exit() {
    CLI::display(s_maze);

    // save to file
    m_fileManager.save(s_maze);
    m_fileManager.save("GENERATION-TIME: " + std::to_string(s_maze.generationTime()));

    std::exit(EXIT_SUCCESS);
}

void Game::robotTurn() {
    // prompt user until valid input
    while (true) {
        char userInput{ CLI::getUserInput() };

        if (tolower(userInput) == 'q') { exit(); }

        std::optional<Direction> dir{ directionFromChar(userInput) };

        if (dir) {
            Position newPos{ s_robot.pos() + dir.value() };
            s_robot.useItem(newPos);
            if (s_robot.canMoveTo(newPos)) {
                Cell cell{ s_maze.cellAt(newPos) };
                if (cell == Cell::item) {
                    s_robot.pickupItem(getRandomItem());
                    std::cout << "\nYou have picked up: " << s_robot.activeItem()->getStr() << '\n';
                }
                else if (cell == Cell::minotaur && !s_minotaur.isKO() && s_minotaur.isAlive()) {
                    s_robot.kill();
                    s_maze.updateCell(s_robot.pos(), Cell::passage);
                    std::cout << "\nYou have died. GG\n";
                    exit();
                }
                else if (cell == Cell::exit) {
                    std::cout << "\nYou have won!!\n";
                    s_maze.updateCells(s_robot.pos(), newPos);
                    exit();
                }
                else if (cell == Cell::minotaur && s_minotaur.isKO()) {
                    return;
                }

                s_maze.updateCells(s_robot.pos(), newPos);
                s_robot.setPosition(newPos);
                return;
            }
        }
        else {
            std::cout << "\nInvalid input\n";
        }
    }
}

void Game::minotaurTurn() {

    if (s_minotaur.isKO()) {
        s_minotaur.reduceKODuration();
        return;
    }
    if (!s_minotaur.isAlive()) {
        return;
    }

    int minotaurX{ s_minotaur.pos().x };
    int minotaurY{ s_minotaur.pos().y };
    int robotX{ s_robot.pos().x };
    int robotY{ s_robot.pos().y };

    // try to kill robot if near
    if ((abs(minotaurX - robotX) == 1 && abs(minotaurY - robotY) == 0) || (abs(minotaurX - robotX) == 0 && abs(minotaurY - robotY) == 1)) {
        if (s_robot.activeItem() && dynamic_cast<Sword*>(s_robot.activeItem())) {
            s_minotaur.kill();
            s_maze.updateCell(s_minotaur.pos(), Cell::passage);
            std::cout << "\nMinotaur tried to attack you, but failed... \nLocate the exit to win!\n";
            return;
        }
        if (s_robot.activeItem() && dynamic_cast<Shield*>(s_robot.activeItem())) {
            s_minotaur.knockOut();
            std::cout << "\nMinotaur tried to attack you, but got stunned by your shield...\n";
            std::cout << "Try to escape while you can ;)\n\n";
            return;
        }

        s_maze.updateCell(s_robot.pos(), Cell::minotaur);
        s_maze.updateCell(s_minotaur.pos(), Cell::passage);
        std::cout << "\nMinotaur have killed you...\nYou could have done better :(\n";
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

