#pragma once
#include <vector>
#include "Settings.h"
#include "../common/Cell.h"
#include "../common/Position.h"

namespace MatrixGenerator {
    struct Data {
        std::vector<std::vector<Cell>> matrix;
        Position enter;
        Position exit;
    };

    Data generate(Settings settings);

} // namespace MatrixGenerator
