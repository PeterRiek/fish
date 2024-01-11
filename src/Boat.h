#pragma once

#include <SDL2/SDL.h>

class Boat
{
public:
    Boat(SDL_Texture *texture, double cost, int range);
    ~Boat();

    SDL_Texture *getTexture();
    double getCost();
    int getRange();

private:
    SDL_Texture *texture;
    double cost;
    int range;
};