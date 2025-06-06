#include "Item.h"
#include "../utils/Random.h"
#include "Sword.h"
#include "Hammer.h"
#include "Shield.h"
#include "Fog.h"
#include <functional>

std::unique_ptr<Item> getRandomItem() {
    std::array<std::function<std::unique_ptr<Item>()>, Item::max_types> items{
        []() {return std::make_unique<Sword>();},
        []() {return std::make_unique<Hammer>();},
        []() {return std::make_unique<Shield>();},
        []() {return std::make_unique<Hammer>();}
    };

    int i{ Random::get(0, Item::Type::max_types - 1) };
    return items[i]();
}