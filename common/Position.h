#pragma once
#include "Direction.h"

struct Position {

    Position operator+(const Direction& dir) {
        return Position{ x + dir.dx, y + dir.dy };
    }

    Position operator+(const Position& other) {
        return { x + other.x, y + other.y };
    }

    Position& operator+=(const Direction& dir) {
        x += dir.dx;
        y += dir.dy;
        return *this;
    }

    bool operator==(const Position& other) {
        return x == other.x && y == other.y;
    }

    int x{};
    int y{};
};
