#include "Item.h"


class Shield : public Item {
public:
    Shield()
        : Item{ Type::shield } {
    }

    void use(Lib::Position pos);

    std::string_view getStr() const override {
        return "Shield";
    }
};