#include "Item.h"


class Hammer : public Item {
public:
    Hammer()
        : Item{ Type::hammer } {
    }

    void use(Lib::Position pos) override;

    std::string_view getStr() const override { return "Hammer"; }
};