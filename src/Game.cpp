#include "Game.h"
#include "GameObject.h"
#include <chrono>

Game::Game() : window(nullptr), renderer(nullptr), isGameRunning(false) {}

Game::~Game() {}

void Game::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return;
    }

    window = SDL_CreateWindow("Fish", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window)
    {
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    renderIntervalMillis = 250;
    updateIntervalMillis = 1000;
    lastRenderTimeMillis = 0;
    lastUpdateTimeMillis = 0;

    isGameRunning = true;

    gameObjects.push_back(new GameObject(renderer, "assets/tmp.png", 100, 100, 50, 50));
}

long long getCurrentTimeMillis()
{
    auto currentTimePoint = std::chrono::system_clock::now();
    auto currentTimeMillis = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTimePoint);
    return currentTimeMillis.time_since_epoch().count();
}

void Game::handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isGameRunning = false;
        }
        if (event.type == SDL_KEYDOWN)
        {
        }
        
    }
}

void Game::update()
{
    if (getCurrentTimeMillis() - lastUpdateTimeMillis < updateIntervalMillis)
        return;
    lastUpdateTimeMillis = getCurrentTimeMillis();
    for (auto &gameObject : gameObjects)
    {
        gameObject->update();
    }
}

void Game::render()
{
    if (getCurrentTimeMillis() - lastRenderTimeMillis < renderIntervalMillis)
        return;
    lastRenderTimeMillis = getCurrentTimeMillis();

    SDL_RenderClear(renderer);

    for (auto &gameObject : gameObjects)
    {
        gameObject->render();
    }

    SDL_RenderPresent(renderer);
}

void Game::cleanup()
{
    for (auto &gameObject : gameObjects)
    {
        delete gameObject;
    }
    gameObjects.clear();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

bool Game::isRunning() const
{
    return isGameRunning;
}
