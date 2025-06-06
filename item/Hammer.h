#include "Item.h"


class Hammer : public Item {
public:
    Hammer()
        : Item{ Type::hammer } {
    }

    std::string_view getStr() override {
        return "Hammer";
    }

private:
};