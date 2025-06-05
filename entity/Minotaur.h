#pragma once
#include "Entity.h"
#include "../maze/Maze.h"


class Minotaur : public Entity {
public:
    explicit Minotaur(Position pos)
        : Entity{ pos } {
    }

    bool canMoveTo(Maze& maze, Position newPos) override;
};