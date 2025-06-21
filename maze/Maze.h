#pragma once
#include <vector>
#include "maze_generator/MazeGenerator.h"
#include "common/Position.h"


class Maze {
public:
    explicit Maze(Lib::MazeData data);

    Maze() = default;

    // check whether entity can move to given position
    bool isWalkable(Lib::Position pos);

    void swapCells(Lib::Position cellPos1, Lib::Position cellPos2);

    void updateCell(Lib::Position pos, Lib::Cell cell);

    // check whether position is within maze bounds
    bool isWithinBounds(Lib::Position pos) const;

    friend std::ostream& operator<< (std::ostream& out, const Maze& maze);
    friend std::ofstream& operator<< (std::ofstream& out, const Maze& maze);
    Lib::Cell& operator[](const Lib::Position& pos);

    /* access methods */
    int numRows() const { return static_cast<int>(m_data.matrix.size()); }
    int numCols() const { return static_cast<int>(m_data.matrix[0].size()); }
    int borderY() const { return static_cast<int>(m_data.matrix.size()) - 1; }
    int borderX() const { return static_cast<int>(m_data.matrix[0].size()) - 1; }
    Lib::Position enterPos() const { return m_data.enter; }
    Lib::Position exitPos() const { return m_data.exit; }
    Lib::Cell cellAt(Lib::Position pos) const { return m_data.matrix[pos.y][pos.x]; }
    void setData(Lib::MazeData data) { m_data = std::move(data); }
    double generationTime() const { return m_generationTime; }
    void setGenerationTime(double time) { m_generationTime = time; }

private:
    Lib::MazeData m_data;
    double m_generationTime{ 0 };
};
