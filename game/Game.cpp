#include "Game.h"

#include <iostream>
#include "../utils/Random.h"
#include "../maze_generator/MazeGenerator.h"
#include "../io/FileManager.h"
#include "Helper.h"
#include "../entity/Robot.h"
#include "../entity/Minotaur.h"
#include "../io/CLI.h"


namespace Game {

    /* Initialize static variables */
    Maze s_maze;
    Robot s_robot;
    Minotaur s_minotaur;

    /* Setup maze */
    void init(int argc, char* argv[]) {
        MazeGenerator generator{ Settings{handleArguments(argc, argv)} };

        s_maze.setData(generator.generate());
        s_robot.setPosition(Helper::getRobotPosition(s_maze.enterPos()));
        s_minotaur.setPosition(Helper::getMinotaurPosition(s_maze.numRows(), s_maze.numCols()));

        s_maze.updateCell(s_robot.pos(), Cell::robot);
        s_maze.updateCell(s_minotaur.pos(), Cell::minotaur);
    }

    void run() {
        while (running()) {
            CLI::display(s_maze);

            robotTurn();
            if (!running())
                exit();
            minotaurTurn();
        }
        exit();
    }

    bool running() {
        return s_robot.isAlive() && s_robot.pos() != s_maze.exitPos();
    }

    void exit() {
        CLI::display(s_maze);

        // save to file
        FileManager fileManager{ "output.txt" };
        fileManager.save(s_maze);
        fileManager.save("GENERATION-TIME: " + std::to_string(s_maze.generationTime()));

        std::exit(EXIT_SUCCESS);
    }

    void robotTurn() {
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

    void minotaurTurn() {

        if (s_minotaur.isKO()) {
            s_minotaur.reduceKODuration();
            return;
        }
        if (!s_minotaur.isAlive() || !s_robot.isAlive()) {
            return;
        }

        s_minotaur.move();
    }

} // namespace Game