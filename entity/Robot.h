#pragma once 

#include <memory>
#include <string_view>
#include "Entity.h"
#include "../item/Item.h"


class Robot : public Entity {
public:
    explicit Robot(Position pos)
        : Entity{ pos } {
    }

    Robot() = default;

    bool canMoveTo(Position newPos) override;

    void pickupItem(std::unique_ptr<Item> item);

    void useItem(Position pos);

    void move(Position pos);

    void defend();

    /* access methods */
    Item* activeItem() { return m_activeItem.get(); }

private:
    std::unique_ptr<Item> m_activeItem{ nullptr };
};