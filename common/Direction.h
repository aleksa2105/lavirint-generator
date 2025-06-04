#pragma once

struct Direction
{
    Direction(int x, int y)
        : dx{ x }, dy{ y } {
    }

    int dx{};
    int dy{};
};
