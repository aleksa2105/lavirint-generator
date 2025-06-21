#pragma once
#include <optional>

namespace Lib {

    struct Direction
    {
        Direction(int x, int y)
            : dx{ x }, dy{ y } {
        }

        int dx{};
        int dy{};
    };

    inline std::optional<Direction> directionFromChar(char c) {
        switch (c)
        {
        case 'w': case 'W': return Direction{ 0, -1 }; // north
        case 'a': case 'A': return Direction{ -1, 0 }; // west
        case 's': case 'S': return Direction{ 0, 1 }; // south
        case 'd': case 'D': return Direction{ 1, 0 }; // east
        default: // wrong input
            return std::nullopt;
        }
    }

}