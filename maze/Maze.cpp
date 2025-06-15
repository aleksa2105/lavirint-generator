#include "Maze.h"
#include <ostream>
#include <fstream>
#include "../game/Game.h"
#include "../item/Fog.h"


Maze::Maze(MazeData data)
    : m_data{ data } {
}

bool Maze::isWalkable(Position pos) {
    Cell cell{ (*this)[pos] };

    if (!isWithinBounds(pos)) // out of maze bounds
        return false;
    if (cell == Cell::wall)
        return false;

    return true;
}

void Maze::swapCells(Position cellPos1, Position cellPos2) {

    Cell& cell1{ (*this)[cellPos1] };
    Cell& cell2{ (*this)[cellPos2] };

    // cell2 is entity
    if (cell1 == Cell::item || cell1 == Cell::exit) {
        cell1 = cell2;
        cell2 = Cell::passage; // destroy item/exit
    }
    // cell1 is entity
    else if (cell2 == Cell::item || cell2 == Cell::exit) {
        cell2 = cell1;
        cell1 = Cell::passage; // destroy item/exit
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

bool Maze::isWithinBounds(Position pos) const {
    if (pos.x <= 0 || pos.y <= 0 || pos.x >= borderX() || pos.y >= borderY()) // out of maze bounds
        return false;

    return true;
}

Cell& Maze::operator[](const Position& pos) {
    return m_data.matrix[pos.y][pos.x];
}

std::ostream& operator<< (std::ostream& out, const Maze& maze) {
    Robot& robot{ Game::s_robot };

    for (int y{ 0 }; y < maze.numRows(); ++y) {
        for (int x{ 0 }; x < maze.numCols(); ++x) {
            // check if robot has fog item active
            if (dynamic_cast<Fog*>(robot.activeItem()) && (abs(robot.pos().x - x) > 1 || abs(robot.pos().y - y) > 1)) {
                out << cellTypeColor(Cell::wall) << cellToChar(Cell::wall) << RESET << ' ';
            }
            else {
                Cell cellType = maze.cellAt({ x, y });
                out << cellTypeColor(cellType) << cellToChar(cellType) << RESET << ' ';
            }
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