#pragma once
#include "../utils/Color.h"

enum class Cell
{
    wall,
    passage,
    enter,
    exit,
    item,
    robot,
    minotaur
};

inline char cellToChar(Cell cell)
{
    switch (cell) {
    case Cell::wall: return '#';
    case Cell::passage: return '.';
    case Cell::enter: return 'E';
    case Cell::exit: return 'X';
    case Cell::item: return '?';
    case Cell::robot: return 'R';
    case Cell::minotaur: return 'M';
    default: return '?';
    }
}

inline const char* cellTypeColor(Cell cell) {
    switch (cell)
    {
    case Cell::robot: return YELLOW;
    case Cell::item: return CYAN;
    case Cell::minotaur: return RED;
    case Cell::wall: return MAGENTA;
    default: return RESET;
    }
}