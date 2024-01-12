#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <tuple>
#include "Rod.h"

class Fish
{
public:
    Fish(SDL_Texture *texture, int rarity, double weight, double size);
    ~Fish();

    double getStrength(int tick, double progress, double hook, Rod *rod);
    std::vector<std::tuple<int, double, SDL_Color>> *getFishingSections(int tick, double progress, double hook, Rod *rod);
    SDL_Texture *getTexture();
    
    int getRarity();
    double getWeight();
    double getSize();

private:
    std::vector<std::tuple<int, double, SDL_Color>> *fishingSections;
    SDL_Texture *texture;
    int rarity;
    double weight;
    double size;
};