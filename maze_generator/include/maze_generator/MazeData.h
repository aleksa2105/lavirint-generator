#pragma once
#include "common/Position.h"
#include "common/Cell.h"
#include <vector>


namespace Lib {

    struct MazeData {
        std::vector<std::vector<Cell>> matrix;
        Position enter;
        Position exit;
    };

}