#include "FishObject.h"
#include "SDL2/SDL_ttf.h"
#include <string>

TTF_Font *font;

FishObject::FishObject(SDL_Renderer *renderer, const char *imagePath, int x, int y, int width, int height, int strength, std::vector<std::tuple<int, int, SDL_Color>> *sections)
    : GameObject(renderer, imagePath, x, y, width, height)
{
    this->strength = strength;
    this->sections = sections;
    progress = 0;
    hook = 0;
    if (TTF_Init() < 0)
        SDL_Quit();
    font = TTF_OpenFont("sans.ttf", 12);
}

FishObject::~FishObject()
{
}

void FishObject::update()
{
    GameObject::update();

    // printf("%d\n", std::get<0>(sections->back()));
    if (hook > std::get<0>(sections->back()) || hook < 0)
    {
        hook = 50;
        progress = -100;
    }

    int p = 0;
    for (auto &section : *sections)
    {
        if (hook > 0 && hook < std::get<0>(section))
        {
            p = std::get<1>(section);
            break;
        }
    }
    progress += p;

    hook += strength;
}

void FishObject::render()
{
    SDL_RenderClear(renderer);

    int prev = 0;
    int y = rect.y;
    int x = rect.x;
    int w = 100;
    for (auto &section : *sections)
    {
        int h = std::get<0>(section) - prev;
        SDL_Color color = std::get<2>(section);
        SDL_Rect filledRect = {x, y, w, h};
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &filledRect);
        y += h;
        prev = std::get<0>(section);
    }
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 255);

    SDL_Rect filledRect = {x + w, 100 + hook - 5, 30, 10};
    SDL_RenderFillRect(renderer, &filledRect);

    SDL_Rect textRect = {0, 0, 200, 50};
    SDL_Color textColor = {0xff, 0xff, 0xff}; // Red color
    std::string progressText = "Progress: " + std::to_string(progress);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, progressText.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    GameObject::render();
}

void FishObject::pull(int pull)
{
    hook -= pull;
}
