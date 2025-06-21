#include "Item.h"


class Fog : public Item {
public:
    Fog()
        : Item{ Type::fog } {
    }

    void use(Lib::Position pos) override;

    std::string_view getStr() const override {
        return "Fog";
    }
};