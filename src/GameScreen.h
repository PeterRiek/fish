#pragma once

#include "Game.h"

class GameScreen
{
public:
    GameScreen();
    ~GameScreen();

    virtual void initialize();
    virtual void handleInput(SDL_Event event);
    virtual void update(SDL_Renderer *renderer);

private:
    Game *game;
};