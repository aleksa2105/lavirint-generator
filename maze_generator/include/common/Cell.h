#pragma once
#include "utils/Color.h"

namespace Lib {

    enum Cell {
        wall,
        passage,
        enter,
        exit,
        item,
        robot,
        minotaur
    };

    inline char cellToChar(Cell cell) {
        switch (cell) {
        case wall: return '#';
        case passage: return '.';
        case enter: return 'E';
        case exit: return 'X';
        case item: return '?';
        case robot: return 'R';
        case minotaur: return 'M';
        default: return '?';
        }
    }

    inline const char* cellTypeColor(Cell cell) {
        switch (cell)
        {
        case robot: return YELLOW;
        case item: return CYAN;
        case minotaur: return RED;
        case wall: return MAGENTA;
        default: return RESET;
        }
    }
}

