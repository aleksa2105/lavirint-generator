#include "Item.h"

class Sword : public Item {
public:
    Sword()
        : Item{ Type::sword } {
    }

    void use(Lib::Position pos) override;

    std::string_view getStr() const override { return "Sword"; }
};