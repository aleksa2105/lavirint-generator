#include <iostream>
#include "game/Game.h"

int main(int argc, char* argv[])
{
    Game game{ argc, argv };
    game.run();
}
