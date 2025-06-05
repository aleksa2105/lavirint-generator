#include "Maze.h"
#include <ostream>
#include "../utils/Utils.h"


Maze::Maze(MazeData data)
    : m_data{ data } {
}

bool Maze::isValidMove(Position pos) {
    Cell cell{ m_data.matrix[pos.y][pos.x] };

    if (pos.x <= 0 || pos.y <= 0 || pos.x >= borderX() || pos.y >= borderY()) // out of maze bounds
        return false;
    if (cell == Cell::wall)
        return false;

    return true;
}

void Maze::swapCells(Position cellPos1, Position cellPos2) {
    Cell temp{ m_data.matrix[cellPos1.y][cellPos1.x] };
    m_data.matrix[cellPos1.y][cellPos1.x] = m_data.matrix[cellPos2.y][cellPos2.x];
    m_data.matrix[cellPos2.y][cellPos2.x] = temp;
}

void Maze::updateCell(Position pos, Cell cell) {
    m_data.matrix[pos.y][pos.x] = cell;
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