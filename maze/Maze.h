#pragma once
#include <vector>
#include "../maze_generator/MazeGenerator.h"
#include "../maze_generator/MazeData.h"
#include "../common/Position.h"


class Maze {
public:
    /* constructor */
    explicit Maze(MazeData data);

    Maze() = default;

    /* methods */
    bool isValidMove(Position pos);

    void swapCells(Position cellPos1, Position cellPos2);

    void updateCell(Position pos, Cell cell);

    friend std::ostream& operator<< (std::ostream& out, const Maze& maze);
    friend std::ofstream& operator<< (std::ofstream& out, const Maze& maze);

    /* access methods */
    int numRows() const { return m_data.matrix.size(); }
    int numCols() const { return m_data.matrix[0].size(); }
    int borderY() const { return m_data.matrix.size() - 1; }
    int borderX() const { return m_data.matrix[0].size() - 1; }
    Position enterPos() const { return m_data.enter; }
    Position exitPos() const { return m_data.exit; }
    double generationTime() { return m_data.generationTime; }
    Cell cellAt(Position pos) const { return m_data.matrix[pos.y][pos.x]; }

private: /* data */
    MazeData m_data;
};
