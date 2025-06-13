#pragma once
#include <vector>
#include "../maze_generator/MazeGenerator.h"
#include "../common/Position.h"


class Maze {
public:
    explicit Maze(MazeData data);

    Maze() = default;

    // check whether entity can move to given position
    bool isValidMove(Position pos);

    void updateCells(Position cellPos1, Position cellPos2);

    void updateCell(Position pos, Cell cell);

    // check whether position is within maze bounds
    bool isWithinBounds(Position pos) const;

    friend std::ostream& operator<< (std::ostream& out, const Maze& maze);
    friend std::ofstream& operator<< (std::ofstream& out, const Maze& maze);
    Cell& operator[](const Position& pos);

    /* access methods */
    int numRows() const { return m_data.matrix.size(); }
    int numCols() const { return m_data.matrix[0].size(); }
    int borderY() const { return m_data.matrix.size() - 1; }
    int borderX() const { return m_data.matrix[0].size() - 1; }
    Position enterPos() const { return m_data.enter; }
    Position exitPos() const { return m_data.exit; }
    double generationTime() const { return m_data.generationTime; }
    Cell cellAt(Position pos) const { return m_data.matrix[pos.y][pos.x]; }
    void setData(MazeData data) { m_data = std::move(data); }

private:
    MazeData m_data;
};
