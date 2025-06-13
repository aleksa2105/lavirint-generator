#pragma once
#include "Entity.h"
#include <iostream>


class Minotaur : public Entity {
public:
    explicit Minotaur(Position pos)
        : Entity{ pos } {
    }

    Minotaur() = default;

    bool canMoveTo(Position newPos) override;

    // Randomly move in one direction. 
    // If robot is encountered, attack will be directed towards him
    void move();

    void knockOut() { KODurationLeft = KODuration; }

    void reduceKODuration();

    bool isKO() const { return KODurationLeft > 0; }

private:
    const int KODuration{ 2 };
    int KODurationLeft{ 0 };
};