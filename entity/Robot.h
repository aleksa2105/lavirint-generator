#pragma once 

#include <memory>
#include <string_view>
#include "Entity.h"
#include "../item/Item.h"


class Robot : public Entity {
public:
    explicit Robot(Lib::Position pos)
        : Entity{ pos } {
    }

    Robot() = default;

    bool canMoveTo(Lib::Position newPos) override;

    void pickupItem(std::unique_ptr<Item> item);

    void useItem(Lib::Position pos);

    void move(Lib::Position pos);

    // Defend against minotaur's attack with active items.
    void defend();

    Item* activeItem() { return m_activeItem.get(); }

private:
    std::unique_ptr<Item> m_activeItem{ nullptr };
};