#pragma once

#include "GameState.h"
#include "Helper.h"
#include "../common/Direction.h"
#include "../entity/Robot.h"
#include "../entity/Minotaur.h"
#include "../io/CLI.h"
#include "../io/FileManager.h"
#include "../item/Item.h"
#include "../maze/Maze.h"
#include "../maze_generator/MazeGenerator.h"
#include "../utils/Random.h"


class Game {
public:
    Game(int argc, char* argv[], std::string_view fileName);

    // main game loop
    void run();

    bool running() const { return m_state == GameState::running; }

    void exit();

    void robotTurn();

    void minotaurTurn();

private:
    GameState m_state;
    MazeGenerator m_mazeGenerator;
    Maze m_maze;
    Robot m_robot;
    Minotaur m_minotaur;
    FileManager m_fileManager;
};