#include "Rod.h"

Rod::Rod(SDL_Texture *texture, double cost, double lure, double pull)
{
    this->texture = texture;
    this->cost = cost;
    this->lure = lure;
    this->pull = pull;
}

Rod::~Rod() {}

SDL_Texture *Rod::getTexture()
{
    return texture;
}

double Rod::getCost()
{
    return cost;
}

double Rod::getLure()
{
    return lure;
}

double Rod::getPull()
{
    return pull;
}