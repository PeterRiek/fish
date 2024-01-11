#include "Fish.h"

Fish::Fish(SDL_Texture *texture, int rarity, double weight, double size)
{
}

Fish::~Fish(){};

double Fish::getStrength(double progress, double hook, Rod *rod)
{
    return 1;
}

SDL_Texture *Fish::getTexture()
{
    return texture;
}


int Fish::getRarity()
{
    return rarity;
}

double Fish::getWeight()
{
    return weight;
}

double Fish::getSize()
{
    return size;
}



