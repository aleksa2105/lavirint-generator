#pragma once 
#include "Entity.h"
#include "../maze/Maze.h"


class Robot : public Entity {
public:
    explicit Robot(Position pos)
        : Entity{ pos } {
    }

    bool canMoveTo(Maze& maze, Position newPos) override;
};