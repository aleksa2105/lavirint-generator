#pragma once
#include "Color.h"
#include "../common/Cell.h"

namespace Utils {
    inline const char* cellTypeColor(Cell cell) {
        switch (cell)
        {
        case Cell::robot: return YELLOW;
        case Cell::item: return CYAN;
        case Cell::minotaur: return RED;
        default: return RESET;
        }
    }
}