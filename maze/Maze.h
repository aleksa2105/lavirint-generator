#pragma once
#include <vector>
#include "../matrix_generator/MatrixGenerator.h"
#include "../common/Position.h"

class Maze {
public:
    /* constructor */
    Maze(Settings settings)
        : m_matrixData{ MatrixGenerator::generate(settings) }
    {
    }

    /* methods */

    /* access methods */
    int numRows() const { return m_matrixData.matrix.size(); }
    int numCols() const { return m_matrixData.matrix[0].size(); }
    Position enterPos() const { return m_matrixData.enter; }
    Position exitPos() const { return m_matrixData.exit; }

private:
    /* data */
    MatrixGenerator::Data m_matrixData;
};
