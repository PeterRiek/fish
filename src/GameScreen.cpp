
#include "Fish.h"
#include "GameScreen.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <iostream>
#include <sstream>

#pragma region GameScreen

GameScreen::GameScreen(Game *game)
{
    this->game = game;
}

GameScreen::~GameScreen() {}

void GameScreen::initialize(void *data) {}

void GameScreen::handleInput(SDL_Event event) {}

void GameScreen::update() {}

void GameScreen::render(SDL_Renderer *renderer) {}

#pragma endregion

#pragma region LuringScreen

LuringScreen::LuringScreen(Game *game) : GameScreen(game) {}

LuringScreen::~LuringScreen() {}

void LuringScreen::initialize(void *data) {}

void LuringScreen::handleInput(SDL_Event event) {}

void LuringScreen::update()
{

}

void LuringScreen::render(SDL_Renderer *renderer) {}

#pragma endregion

#pragma region FishingScreen

FishingScreen::FishingScreen(Game *game) : GameScreen(game) {}

FishingScreen::~FishingScreen() {}

void FishingScreen::initialize(void *data)
{
    Fish *f = (Fish *)data;
    if (!f)
    {
        fprintf(stderr, "could not load data to initialize gamescreen.\n");
        return;
    }
    tick = 0;
    hook = 100;
    fish = f;
    isPulling = false;

    player = game->getPlayer();
    progress = 0;
}

void FishingScreen::handleInput(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_SPACE)
            isPulling = true;
    }

    if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_SPACE)
            isPulling = false;
    }
}

void FishingScreen::update()
{
    ++tick;

    fishingSections = fish->getFishingSections(tick, progress, hook, player->getRod());

    double nHook = hook;
    if (isPulling)
        nHook -= player->getRod()->getPull();
    nHook += fish->getStrength(tick, progress, hook, nullptr);
    if (nHook < 200 && nHook > 0)
        hook = nHook;

    double p = 0;
    for (auto &section : *fishingSections)
    {
        if (hook > 0 && hook < section.upperBound)
        {
            p = section.modifier;
            break;
        }
    }

    if (progress + p >= 0)
        progress += p;
    else
        progress = 0;
    if (progress > 100)
        game->setScreen(1, fish);
}

void FishingScreen::render(SDL_Renderer *renderer)
{
    SDL_Rect bgRect = {0, 0, 400, 400};
    SDL_RenderCopy(renderer, game->getTextureManager()->loadTexture("assets/bg.png"), nullptr, &bgRect);

    int scale = 2;

    /* ===[]=== */
    int sy = 100;
    int prev = 0;
    int x = 250;
    int y = sy;
    int w = 100;
    for (auto &section : *fishingSections)
    {
        int r = section.upperBound;
        int h = r - prev;
        SDL_Color c = section.color;
        SDL_Rect fillRect = {x, y, w, h};
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(renderer, &fillRect);
        y += h;
        prev = r;
    }

    int hookSize = 40;
    SDL_Rect hookRect = {x + w - hookSize / 2, sy + hook - hookSize / 2, hookSize, hookSize};
    SDL_RenderCopy(renderer, game->getTextureManager()->loadTexture("assets/hook.png"), nullptr, &hookRect);

    int progH = 200;
    SDL_Rect progBgRect = {20, 20, 5, progH};
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderFillRect(renderer, &progBgRect);
    SDL_Rect progRect = {20, 20, 5, progress / 100 * progH};
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderFillRect(renderer, &progRect);

    // SDL_Rect fishRect = {0, 0, 100, 100};
    // SDL_RenderCopy(renderer, fish->getTexture(), nullptr, &fishRect);
}

#pragma endregion

#pragma region FishCaughtScreen

FishCaughtScreen::FishCaughtScreen(Game *game) : GameScreen(game) {}

FishCaughtScreen::~FishCaughtScreen() {}

void FishCaughtScreen::initialize(void *data)
{
    Fish *fish = (Fish *)data;
    player = game->getPlayer();
    if (!fish)
    {
        fprintf(stderr, "could not load data to initialize gamescreen.\n");
        return;
    }
    this->fish = fish;

    // printf("%p\t%s\n", t, t.c_str());

    printf("[Caught Fish]\n\tsize: %f m\n\tweight: %f kg\n", fish->getSize(), fish->getWeight());
    // player->getInventory().push_back(fish);
}

void FishCaughtScreen::handleInput(SDL_Event event)
{
    if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_SPACE)
            return;
    }
}

void FishCaughtScreen::update()
{
}

void FishCaughtScreen::render(SDL_Renderer *renderer)
{
    SDL_Rect rect = {100, 100, 200, 200};
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
    SDL_RenderFillRect(renderer, &rect);

    // SDL_Rect textRect = {100, 100, 200, 20};
    // SDL_Color textColor = {0xff, 0xff, 0xff};
    SDL_Color textColor = {0x00, 0x00, 0x00, 0xff};
    std::stringstream ssR;
    ssR << "Rarity: " << fish->getRarity().text;
    std::stringstream ssW;
    ssW << "Weight: " << fish->getWeight() << "kg";
    std::stringstream ssS;
    ssS << "Size: " << fish->getSize() << "m";

    

    SDL_Surface *surface = TTF_RenderText_Blended(game->getBodyFont(), ssR.str().c_str(), textColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destRect = {100, 100, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    surface = TTF_RenderText_Blended(game->getBodyFont(), ssW.str().c_str(), textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    destRect = {100, 120, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    surface = TTF_RenderText_Blended(game->getBodyFont(), ssS.str().c_str(), textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    destRect = {100, 140, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);


    // SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}

#pragma endregion