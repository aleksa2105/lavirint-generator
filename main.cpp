#include <iostream>
#include "game/Game.h"

const char* g_outputFile{ "output.txt" };

int main(int argc, char* argv[])
{
    Game game{ argc, argv, g_outputFile };
    game.run();
}
