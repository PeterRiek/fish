#pragma once

#include <SDL2/SDL.h>
#include <vector>

class GameObject;  // Forward declaration

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

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isGameRunning;
    long long renderIntervalMillis;
    long long updateIntervalMillis;
    long long lastRenderTimeMillis;
    long long lastUpdateTimeMillis;
    std::vector<GameObject*> gameObjects;
};