#pragma once

#include "Game.h"
#include "Fish.h"

class Game;

class GameScreen
{
public:
    GameScreen(Game *game);
    ~GameScreen();

    virtual void initialize(void *data);
    virtual void handleInput(SDL_Event event);
    virtual void update();
    virtual void render(SDL_Renderer *renderer);

protected:
    Game *game;
    int tick;
};

class LuringScreen : public GameScreen
{
public:
    LuringScreen(Game *game);
    ~LuringScreen();

    void initialize(void *data) override;
    void handleInput(SDL_Event event) override;
    void update() override;
    void render(SDL_Renderer *renderer) override;

private:
    Player *player;
};

class FishingScreen : public GameScreen
{
public:
    FishingScreen(Game *game);
    ~FishingScreen();

    void initialize(void *data) override;
    void handleInput(SDL_Event event) override;
    void update() override;
    void render(SDL_Renderer *renderer) override;

private:
    Player *player;
};

class FishCaughtScreen : public GameScreen
{
public:
    FishCaughtScreen(Game *game);
    ~FishCaughtScreen();

    void initialize(void *data) override;
    void handleInput(SDL_Event event) override;
    void update() override;
    void render(SDL_Renderer *renderer) override;

private:
    Player *player;
};