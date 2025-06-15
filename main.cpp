#include "game/Game.h"
#include "io/FileManager.h"


int main(int argc, char* argv[]) {
    Game::init(argc, argv);
    Game::run();
}
