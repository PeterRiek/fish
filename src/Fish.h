#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <tuple>
#include <string>
#include "Rod.h"

struct FishingSection {
    int upperBound;
    double modifier;
    SDL_Color color;
};

struct Rarity {
    int rarity;
    char* text;
    SDL_Color color;
};

class Fish
{
public:
    Fish(SDL_Texture *texture, struct Rarity rarity, double weight, double size);
    ~Fish();

    double getStrength(int tick, double progress, double hook, Rod *rod);
    std::vector<struct FishingSection> *getFishingSections(int tick, double progress, double hook, Rod *rod);
    SDL_Texture *getTexture();
    
    struct Rarity getRarity();
    double getWeight();
    double getSize();

private:
    std::vector<struct FishingSection> *fishingSections;
    SDL_Texture *texture;
    struct Rarity rarity;
    double weight;
    double size;
};