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

    void knockOut() { KODurationLeft = KODuration; }
    void reduceKODuration() {
        std::cout << "\nMinotaur is knocked down for " << KOLeft() << " more move(s)\n\n";
        --KODurationLeft;
    }
    bool isKO() const { return KODurationLeft > 0; }
    int KOLeft() const { return KODurationLeft; }

private:
    const int KODuration{ 2 };
    int KODurationLeft{ 0 };
};