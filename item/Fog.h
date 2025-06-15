#include "Item.h"


class Fog : public Item {
public:
    Fog()
        : Item{ Type::fog } {
    }

    void use(Position pos) override;

    std::string_view getStr() const override {
        return "Fog";
    }
};