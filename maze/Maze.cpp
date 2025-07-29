#include "Maze.h"
#include <ostream>
#include <fstream>
#include "../game/Game.h"
#include "../item/Fog.h"
#include "utils/Color.h"


Maze::Maze(Lib::MazeData data)
    : m_data{ data } {
}

bool Maze::isWalkable(Lib::Position pos) {
    Lib::Cell cell{ (*this)[pos] };

    if (!isWithinBounds(pos)) // out of maze bounds
        return false;
    if (cell == Lib::Cell::wall)
        return false;

    return true;
}

void Maze::swapCells(Lib::Position cellPos1, Lib::Position cellPos2) {

    Lib::Cell& cell1{ (*this)[cellPos1] };
    Lib::Cell& cell2{ (*this)[cellPos2] };

    // cell2 is entity
    if (cell1 == Lib::Cell::item || cell1 == Lib::Cell::exit) {
        cell1 = cell2;
        cell2 = Lib::Cell::passage; // destroy item/exit
    }
    // cell1 is entity
    else if (cell2 == Lib::Cell::item || cell2 == Lib::Cell::exit) {
        cell2 = cell1;
        cell1 = Lib::Cell::passage; // destroy item/exit
    }
    else {
        Lib::Cell temp{ cell1 };
        cell1 = cell2;
        cell2 = temp;
    }
}

void Maze::updateCell(Lib::Position pos, Lib::Cell cell) {
    (*this)[pos] = cell;
}

bool Maze::isWithinBounds(Lib::Position pos) const {
    if (pos.x <= 0 || pos.y <= 0 || pos.x >= borderX() || pos.y >= borderY()) // out of maze bounds
        return false;

    return true;
}

Lib::Cell& Maze::operator[](const Lib::Position& pos) {
    return m_data.matrix[pos.y][pos.x];
}

std::ostream& operator<< (std::ostream& out, const Maze& maze) {
    Robot& robot{ Game::s_robot };

    for (int y{ 0 }; y < maze.numRows(); ++y) {
        for (int x{ 0 }; x < maze.numCols(); ++x) {
            // check if robot has fog item active
            if (dynamic_cast<Fog*>(robot.activeItem()) &&
                robot.activeItem()->duration() > 0 &&
                (abs(robot.pos().x - x) > 1 || abs(robot.pos().y - y) > 1)) {
                out << Lib::cellTypeColor(Lib::Cell::wall) << Lib::cellToChar(Lib::Cell::wall) << RESET << ' ';
            }
            else {
                Lib::Cell cellType = maze.cellAt({ x, y });
                out << Lib::cellTypeColor(cellType) << Lib::cellToChar(cellType) << RESET << ' ';
            }
        }
        out << '\n';
    }
    return out;
}

std::ofstream& operator<< (std::ofstream& out, const Maze& maze) {
    for (int y{ 0 }; y < maze.numRows(); ++y) {
        for (int x{ 0 }; x < maze.numCols(); ++x) {
            Lib::Cell cell{ maze.cellAt({ x, y }) };
            out << Lib::cellToChar(cell) << ' ';
        }
        out << '\n';
    }
    return out;
}