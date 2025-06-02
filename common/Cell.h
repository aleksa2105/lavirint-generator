#pragma once

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
    switch (cell)
    {
    case Cell::wall:
        return '#';
    case Cell::passage:
        return ' ';
    case Cell::enter:
        return 'E';
    case Cell::exit:
        return 'X';
    case Cell::item:
        return '*';
    case Cell::robot:
        return 'R';
    case Cell::minotaur:
        return 'M';
    default:
        return '?';
    }
}
