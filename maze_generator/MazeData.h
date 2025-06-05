#pragma once
#include <vector>
#include "../common/Position.h"
#include "../common/Cell.h"


struct MazeData {
    std::vector<std::vector<Cell>> matrix;
    Position enter;
    Position exit;
    double generationTime{};
};