#pragma once

#include "../maze/Maze.h"
#include "common/Position.h"


class Entity {
protected:
    // make it not possible to instantiate Entity
    explicit Entity(Lib::Position pos)
        : m_pos{ pos }, m_isAlive{ true } {
    }

    Entity() = default;

public:
    virtual ~Entity() = default;

    // return true if entity can move to given position
    virtual bool canMoveTo(Lib::Position newPos) = 0;

    void setPosition(Lib::Position newPos) { m_pos = newPos; }

    void kill() { m_isAlive = false; }

    Lib::Position pos() const { return m_pos; }

    bool isAlive() const { return m_isAlive; }

protected:
    Lib::Position m_pos;
    bool m_isAlive{ true };
};