#include <iostream>
#include "game/Game.h"


int main(int argc, char* argv[])
{
    Game::init(argc, argv);
    Game::run();
}
