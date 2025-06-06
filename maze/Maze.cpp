#include "Maze.h"
#include <ostream>
#include <fstream>
#include "../utils/Utils.h"


Maze::Maze(MazeData data)
    : m_data{ data } {
}

bool Maze::isValidMove(Position pos) {
    Cell cell{ (*this)[pos] };

    if (pos.x <= 0 || pos.y <= 0 || pos.x >= borderX() || pos.y >= borderY()) // out of maze bounds
        return false;
    if (cell == Cell::wall)
        return false;

    return true;
}

void Maze::updateCells(Position cellPos1, Position cellPos2) {
    Cell& cell1{ (*this)[cellPos1] };
    Cell& cell2{ (*this)[cellPos2] };

    // cell2 is entity
    if (cell1 == Cell::item || cell1 == Cell::exit) {
        cell1 = cell2;
        cell2 = Cell::passage;
    }
    // cell1 is entity
    else if (cell2 == Cell::item || cell2 == Cell::exit) {
        cell2 = cell1;
        cell1 = Cell::passage;
    }
    else {
        Cell temp{ cell1 };
        cell1 = cell2;
        cell2 = temp;
    }
}

void Maze::updateCell(Position pos, Cell cell) {
    (*this)[pos] = cell;
}

Cell& Maze::operator[](const Position& pos) {
    return m_data.matrix[pos.y][pos.x];
}

std::ostream& operator<< (std::ostream& out, const Maze& maze) {
    // clear console
    for (int i{ 0 }; i < g_consoleLines; ++i)
        out << '\n';

    for (int y{ 0 }; y < maze.numRows(); ++y) {
        for (int x{ 0 }; x < maze.numCols(); ++x) {
            Cell cellType = maze.cellAt({ x, y });
            out << Utils::cellTypeColor(cellType) << cellToChar(cellType) << RESET << ' ';
        }
        out << '\n';
    }
    return out;
}

std::ofstream& operator<< (std::ofstream& out, const Maze& maze) {
    for (int y{ 0 }; y < maze.numRows(); ++y) {
        for (int x{ 0 }; x < maze.numCols(); ++x) {
            Cell cell{ maze.cellAt({ x, y }) };
            out << cellToChar(cell) << ' ';
        }
        out << '\n';
    }
    return out;
}