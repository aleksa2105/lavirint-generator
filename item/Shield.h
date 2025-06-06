#include "Item.h"


class Shield : public Item {
public:
    Shield()
        : Item{ Type::shield } {
    }

    std::string_view getStr() override {
        return "Shield";
    }

private:
};