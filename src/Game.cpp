#include "Game.h"
#include "GameObject.h"
#include "FishObject.h"
#include <chrono>

Game::Game() : window(nullptr), renderer(nullptr), isGameRunning(false), gameScreen(nullptr) {}

Game::~Game() {}

void Game::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return;
    }

    window = SDL_CreateWindow("Fish", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_SHOWN);
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
    textureManager = new TextureManager(renderer);

    renderIntervalMillis = 30; // 33.3 times / second
    updateIntervalMillis = 50; // 20 times / second
    lastRenderTimeMillis = 0;
    lastUpdateTimeMillis = 0;


    gameScreens.push_back(new FishingScreen(this));
    gameScreens.push_back(new FishCaughtScreen(this));

    Rod *rod = new Rod(nullptr, 100, 1, 2);
    player = new Player();
    player->setRod(rod);

    printf("rod_pull=%f", rod->getPull());
    Fish *fish = new Fish(textureManager->loadTexture("assets/fish.png"), 1, 10.0, 6.0);


    setScreen(0, fish);

    isGameRunning = true;
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
        if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
        {
            isGameRunning = false;
            return;
        }
        if(gameScreen)
            gameScreen->handleInput(event);
    }
}

void Game::update()
{
    if (getCurrentTimeMillis() - lastUpdateTimeMillis < updateIntervalMillis)
        return;
    lastUpdateTimeMillis = getCurrentTimeMillis();
    if (gameScreen)
        gameScreen->update();
}

void Game::render()
{
    if (getCurrentTimeMillis() - lastRenderTimeMillis < renderIntervalMillis)
        return;
    lastRenderTimeMillis = getCurrentTimeMillis();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    if (gameScreen)
        gameScreen->render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::cleanup()
{
    // for (auto &gameScreen : gameScreens)
    // {
    //     delete gameScreen;
    // }
    gameScreens.clear();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Game::setScreen(size_t screenIdx, void *data)
{
    if (screenIdx >= gameScreens.size())
        return;

    gameScreen = gameScreens[screenIdx];
    gameScreen->initialize(data);
}

bool Game::isRunning() const
{
    return isGameRunning;
}

TextureManager *Game::getTextureManager()
{
    return textureManager;
}

Player *Game::getPlayer()
{
    return player;
}