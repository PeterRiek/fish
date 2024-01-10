#include <SDL2/SDL.h>
#include "Game.h"

int main(int argc, char **argv)
{
    Game game;
    game.initialize();
    while (game.isRunning()) {
        game.handleInput();
        game.update();
        game.render();
    }
    game.cleanup();
    return 0;
}