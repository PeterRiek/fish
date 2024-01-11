#pragma once

#include <SDL2/SDL.h>

class Rod
{
public:
    Rod(SDL_Texture *texture, double cost, double lure, double pull);
    ~Rod();

    SDL_Texture *getTexture();
    double getCost();
    double getLure();
    double getPull();

private:
    SDL_Texture *texture;
    double cost;
    double lure;
    double pull;
};