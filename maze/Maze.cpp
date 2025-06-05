#include "Maze.h"
#include <ostream>
#include "../utils/Utils.h"


Maze::Maze(MazeGenerator::MazeData data)
    : m_data{ data } {
}

std::ostream& operator<< (std::ostream& out, const Maze& maze) {
    // clear console
    for (int i{ 0 }; i < g_consoleLines; ++i)
        out << '\n';

    for (int row{ 0 }; row < maze.numRows(); ++row) {
        for (int col{ 0 }; col < maze.numCols(); ++col) {
            Cell cellType = maze.m_data.matrix[row][col];
            out << Utils::cellTypeColor(cellType) << cellToChar(cellType) << Utils::cellTypeColor(cellType);
            out << ' ';
        }
        out << '\n';
    }
    return out;
}