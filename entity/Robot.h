#pragma once 

#include <memory>
#include "Entity.h"
#include "../maze/Maze.h"
#include "../item/Item.h"
#include <string_view>


class Robot : public Entity {
public:
    explicit Robot(Position pos)
        : Entity{ pos } {
    }

    bool canMoveTo(Maze& maze, Position newPos) override;

    void pickupItem(std::unique_ptr<Item> item) {
        m_activeItem = std::move(item);
    }

    void encounterMinotaur();

    std::string_view activeItemStr() const;

private:
    std::unique_ptr<Item> m_activeItem{ nullptr };
};