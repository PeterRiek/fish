#include "Boat.h"

Boat::Boat(SDL_Texture *texture, double cost, int range)
{
    this->texture = texture;
    this->cost = cost;
    this->range = range;
}

Boat::~Boat() {}

SDL_Texture *Boat::getTexture()
{
    return texture;
}

double Boat::getCost()
{
    return cost;
}

int Boat::getRange()
{
    return range;
}