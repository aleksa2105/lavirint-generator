#pragma once
#include <vector>
#include "../maze_generator/MazeGenerator.h"
#include "../common/Position.h"

class Maze {
public:
    /* constructor */
    explicit Maze(MazeGenerator::MazeData data);

    /* methods */
    friend std::ostream& operator<< (std::ostream& out, const Maze& maze);

    /* access methods */
    int numRows() const { return m_data.matrix.size(); }
    int numCols() const { return m_data.matrix[0].size(); }
    Position enterPos() const { return m_data.enter; }
    Position exitPos() const { return m_data.exit; }

private:
    /* data */
    MazeGenerator::MazeData m_data;
};
