#pragma once
#include "../common/Position.h"
#include "../maze/Maze.h"


class Entity {
public:
    // return true if entity can move to given position
    virtual bool canMoveTo(Position newPos) = 0;

    void setPosition(Position newPos) { m_pos = newPos; }

    void kill() { m_isAlive = false; }

    Position pos() const { return m_pos; }
    bool isAlive() const { return m_isAlive; }

protected:
    // make it not possible to instantiate Entity
    Entity(Position pos)
        : m_pos{ pos }, m_isAlive{ true } {
    }
    Entity() = default;
    ~Entity() = default;

protected:
    Position m_pos;
    bool m_isAlive{ true };
};