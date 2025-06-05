#pragma once
#include "../common/Position.h"
#include "../maze/Maze.h"


class Entity {
public:
    // return true if entity can move to given position
    virtual bool canMoveTo(Maze& maze, Position newPos) = 0;

    void updatePosition(Position newPos) { m_pos = newPos; }

    Position pos() const { return m_pos; }

protected:
    // make it not possible to instantiate Entity
    Entity(Position pos)
        : m_pos{ pos }, m_isAlive{ true } {
    }
    ~Entity() = default;
private:
    Position m_pos;
    bool m_isAlive{ true };
};