#include "Item.h"


class Fog : public Item {
public:
    Fog()
        : Item{ Type::fog } {
    }

    std::string_view getStr() override {
        return "Fog";
    }

private:
};