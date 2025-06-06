#include "Game.h"
#include "../utils/Random.h"
#include "../io/FileManager.h"
#include <iostream>

Game::Game(int argc, char* argv[], std::string_view fileName)
    : m_state{ GameState::running }
    , m_mazeGenerator{ Settings{handleArguments(argc, argv)} }
    , m_maze{ m_mazeGenerator.generate() }
    , m_robot{ Helper::getRobotPosition(m_maze.enterPos()) }
    , m_minotaur{ Helper::getMinotaurPosition(m_maze.numRows(), m_maze.numCols()) }
    , m_fileManager{ fileName }
{
    // place entities
    m_maze.updateCell(m_robot.pos(), Cell::robot);
    m_maze.updateCell(m_minotaur.pos(), Cell::minotaur);
}

void Game::run() {
    while (running()) {
        CLI::display(m_maze);

        robotTurn();
        if (!running())
            break;

        minotaurTurn();
    }
    exit();
}

void Game::exit() {
    CLI::display(m_maze);
    std::cout << "Exited with state: " << gameStateStr(m_state) << '\n';

    // save to file
    m_fileManager.save(m_maze);
    m_fileManager.save("GENERATION-TIME: " + std::to_string(m_maze.generationTime()));

    std::exit(EXIT_SUCCESS);
}

void Game::robotTurn() {
    char userInput{ CLI::getUserInput() };

    if (tolower(userInput) == 'q') {
        m_state = GameState::user_exit;
        return;
    }

    std::optional<Direction> dir{ directionFromChar(userInput) };
    if (!dir.has_value()) {
        std::cout << "Invalid input\n";
    }
    else {
        Position newPos{ m_robot.pos() + dir.value() };
        if (m_robot.canMoveTo(m_maze, newPos)) {

            // 1: robot exited the maze
            if (newPos == m_maze.exitPos()) {
                m_state = GameState::robot_won;
            }
            // 2: robot encountered minotaur
            else if (newPos == m_minotaur.pos()) {
                m_maze.updateCell(m_robot.pos(), Cell::passage);
                m_state = GameState::minotaur_won;
                return;
            }
            // 3. pickup item
            else if (m_maze.cellAt(newPos) == Cell::item) {
                m_robot.pickupItem(getRandomItem());
                std::cout << "You have picked up: " << m_robot.activeItemStr() << '\n';
            }

            m_maze.updateCells(m_robot.pos(), newPos);
            m_robot.updatePosition(newPos);
        }
    }
}

void Game::minotaurTurn() {
    int minotaurX{ m_minotaur.pos().x };
    int minotaurY{ m_minotaur.pos().y };
    int robotX{ m_robot.pos().x };
    int robotY{ m_robot.pos().y };

    // try to kill robot if near
    if ((abs(minotaurX - robotX) == 1 && abs(minotaurY - robotY) == 0) || (abs(minotaurX - robotX) == 0 && abs(minotaurY - robotY) == 1)) {
        m_maze.updateCell(m_robot.pos(), Cell::minotaur);
        m_maze.updateCell(m_minotaur.pos(), Cell::passage);
        m_state = GameState::minotaur_won;
        return;
    }

    // add all available directions to vector and select one randomly
    std::vector<Direction> availableDir{};
    Position curPos{ m_minotaur.pos() };
    if (m_minotaur.canMoveTo(m_maze, curPos + Direction{ 0, -1 })) availableDir.emplace_back(0, -1); // north
    if (m_minotaur.canMoveTo(m_maze, curPos + Direction{ 0, 1 })) availableDir.emplace_back(0, 1); // south
    if (m_minotaur.canMoveTo(m_maze, curPos + Direction{ -1, 0 })) availableDir.emplace_back(-1, 0); // west
    if (m_minotaur.canMoveTo(m_maze, curPos + Direction{ 1, 0 })) availableDir.emplace_back(1, 0); // east

    // randomly select direction
    int randIdx = Random::get(0, static_cast<int>(availableDir.size()) - 1);
    Direction dir = availableDir[randIdx];
    Position newPos{ curPos + dir };

    // update maze and minotaur data
    m_maze.updateCells(curPos, newPos);
    m_minotaur.updatePosition(newPos);
}

