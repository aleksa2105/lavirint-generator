#include "Game.h"
#include "../utils/Random.h"
#include <iostream>

Game::Game(int argc, char* argv[])
    : m_state{ GameState::running }
    , m_mazeGenerator{ Settings{handleArguments(argc, argv)} }
    , m_maze{ m_mazeGenerator.generate() }
    , m_robot{ getRobotPosition(m_maze.enterPos()) }
    , m_minotaur{ getMinotaurPosition(m_maze.numRows(), m_maze.numCols()) }
{
    m_maze.updateCell(m_robot.pos(), Cell::robot);
    m_maze.updateCell(m_minotaur.pos(), Cell::minotaur);
}

void Game::run() {
    while (true) {
        CLI::display(m_maze);

        char userInput{ CLI::getUserInput() };

        if (userInput == 'q' || userInput == 'Q') {
            m_state = GameState::user_exit;
            exit();
        }

        std::optional<Direction> dir{ directionFromInput(userInput) };
        if (!dir.has_value()) {
            std::cout << "Invalid input\n";
        }
        else {
            Position newPos{ m_robot.pos() + dir.value() };
            if (m_robot.canMoveTo(m_maze, newPos)) {
                m_maze.swapCells(m_robot.pos(), newPos);
                m_robot.updatePosition(newPos);
            }
        }
    }
}

void Game::exit() {
    CLI::display(m_maze);
    std::cout << "Exited with state: " << gameStateStr(m_state) << '\n';

    std::exit(EXIT_SUCCESS);
}

std::optional<Direction> Game::directionFromInput(char c) {
    switch (c)
    {
    case 'w': case 'W': return Direction{ 0, -1 }; // north
    case 'a': case 'A': return Direction{ -1, 0 }; // west
    case 's': case 'S': return Direction{ 0, 1 }; // south
    case 'd': case 'D': return Direction{ 1, 0 }; // east
    default: // wrong input
        return std::nullopt;
    }
}