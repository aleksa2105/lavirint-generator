#pragma once
#include <string_view>
#include <memory>


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

    Item(Type type)
        : m_type{ type }, m_duration{ g_itemDuration } {
    }

    virtual ~Item() = default;

    virtual std::string_view getStr() = 0;

private:
    int m_duration{ g_itemDuration };
    Type m_type;
};

std::unique_ptr<Item> getRandomItem();

std::string_view itemStr(const Item& item);
