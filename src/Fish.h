#pragma once

#include <SDL2/SDL.h>
#include "Rod.h"

class Fish
{
public:
    Fish(SDL_Texture *texture, int rarity, double weight, double size);
    ~Fish();

    double getStrength(double progress, double hook, Rod *rod);

    SDL_Texture *getTexture();
    int getRarity();
    double getWeight();
    double getSize();

private:
    SDL_Texture *texture;
    int rarity;
    double weight;
    double size;
};