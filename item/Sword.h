#include "Item.h"


class Sword : public Item {
public:
    Sword()
        : Item{ Type::sword } {
    }

    std::string_view getStr() override {
        return "Sword";
    }

private:
};