#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <cstdio>
#include "Fish.h"
#include "Boat.h"
#include "Rod.h"
#include "Player.h"
#include "GameScreen.h"
#include "TextureManager.h"


class GameObject;  // Forward declaration
class GameScreen;

class Game {
public:
    Game();
    ~Game();

    void initialize();
    void handleInput();
    void update();
    void render();
    void cleanup();
    void setScreen(size_t screenIdx, void *data);
    bool isRunning() const;
    TextureManager *getTextureManager();
    Player *getPlayer();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool isGameRunning;
    long long renderIntervalMillis;
    long long updateIntervalMillis;
    long long lastRenderTimeMillis;
    long long lastUpdateTimeMillis;
    GameScreen *gameScreen;
    std::vector<GameScreen *> gameScreens;
    TextureManager *textureManager;

    Player *player;
};