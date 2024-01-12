
#include "Fish.h"
#include "GameScreen.h"

GameScreen::GameScreen(Game *game)
{
    this->game = game;
}

GameScreen::~GameScreen() {}

void GameScreen::initialize(void *data) {}

void GameScreen::handleInput(SDL_Event event) {}

void GameScreen::update() {}

void GameScreen::render(SDL_Renderer *renderer) {}

LuringScreen::LuringScreen(Game *game) : GameScreen(game) {}

LuringScreen::~LuringScreen() {}

void LuringScreen::initialize(void *data) {}

void LuringScreen::handleInput(SDL_Event event) {}

void LuringScreen::update() {}

void LuringScreen::render(SDL_Renderer *renderer) {}



FishingScreen::FishingScreen(Game *game) : GameScreen(game) {}

FishingScreen::~FishingScreen() {}

Fish *fish;
bool isPulling;
double hook;
double progress;
std::vector<std::tuple<int, double, SDL_Color>> *sections;
SDL_Texture *hookTex;
SDL_Texture *bgText;


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

    hookTex = game->getTextureManager()->loadTexture("assets/hook.png");
    bgText = game->getTextureManager()->loadTexture("assets/bg.png");

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

    sections = fish->getFishingSections(tick, progress, hook, player->getRod());

    double nHook = hook;
    if (isPulling)
        nHook-= player->getRod()->getPull();
    nHook += fish->getStrength(tick, progress, hook, nullptr);
    if (nHook < 200 && nHook > 0)
        hook = nHook;


    double p = 0;
    for (auto &section : *sections)
    {
        if (hook > 0 && hook < std::get<0>(section))
        {
            p = std::get<1>(section);
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
    SDL_RenderCopy(renderer, bgText, nullptr, &bgRect);



    int scale = 2;

    /* ===[]=== */
    int sy = 100;
    int prev = 0;
    int x = 250;
    int y = sy;
    int w = 100;
    for (auto &section : *sections)
    {
        int r = std::get<0>(section);
        int h  = r - prev;
        SDL_Color c = std::get<2>(section);
        SDL_Rect fillRect = {x, y, w, h};
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(renderer, &fillRect);
        y += h;
        prev = r;
    }

    int hookSize = 40;
    SDL_Rect hookRect = {x + w - hookSize/2, sy + hook - hookSize/2, hookSize, hookSize};
    SDL_RenderCopy(renderer, hookTex, nullptr, &hookRect);

    int progH = 200;
    SDL_Rect progBgRect = {20, 20, 5, progH};
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderFillRect(renderer, &progBgRect);
    SDL_Rect progRect = {20, 20, 5, progress/100*progH};
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderFillRect(renderer, &progRect);


    // SDL_Rect fishRect = {0, 0, 100, 100};
    // SDL_RenderCopy(renderer, fish->getTexture(), nullptr, &fishRect);
}


FishCaughtScreen::FishCaughtScreen(Game *game) : GameScreen(game) {}

FishCaughtScreen::~FishCaughtScreen() {}

void FishCaughtScreen::initialize(void *data)
{
    Fish *f = (Fish *)data;
    player = game->getPlayer();
    if (!f)
    {
        fprintf(stderr, "could not load data to initialize gamescreen.\n");
        return;
    }
    printf("[Caught Fish]\n\trarity: %d\n\tsize: %f m\n\tweight: %f kg\n", f->getRarity(), f->getSize(), f->getWeight());
    player->getInventory().push_back(f);
}

void FishCaughtScreen::handleInput(SDL_Event event)
{
    if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_SPACE)
            isPulling = false;
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
}