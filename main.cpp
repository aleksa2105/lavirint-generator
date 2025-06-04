#include <iostream>
#include "maze_generator/MazeGenerator.h"
#include "maze/Maze.h"

int main(int argc, char* argv[])
{
    Settings settings{ handleArguments(argc, argv) };
    MazeGenerator mg{ settings };

    Maze maze{ mg.generate() };
    std::cout << maze;
}
