#pragma once
#include <string_view>
#include <memory>
#include "common/Position.h"

constexpr int g_itemDuration{ 3 };


class Item {
public:
    enum Type {
        sword,
        hammer,
        shield,
        fog,
        max_types
    };

protected: // make it not possible to instantiate Item
    explicit Item(Type type)
        : m_type{ type }, m_duration{ g_itemDuration } {
    }

    Item() = default;

public:
    virtual ~Item() = default;

    virtual void use(Lib::Position pos) = 0;

    // return true if duration of the item is expired
    bool isBroken() const { return m_duration <= 0; }

    int duration() const { return m_duration; }

    void reduceDuration() { --m_duration; }

    virtual std::string_view getStr() const = 0;

    friend std::ostream& operator<<(std::ostream& out, const Item& item);

protected:
    int m_duration{ g_itemDuration };
    Type m_type;
};

std::unique_ptr<Item> getRandomItem();