#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "GameScreen.h"

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
    bool isRunning() const;
    void changeScreen(int screen);

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
    std::vector<GameObject *> gameObjects;
    bool isPulling;
    int pullStrength;
};