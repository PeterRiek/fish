#include "Fish.h"

Fish::Fish(SDL_Texture *texture, struct Rarity rarity, double weight, double size)
{
    this->texture = texture;
    this->rarity = rarity;
    this->weight = weight;
    this->size = size;

    fishingSections = new std::vector<struct FishingSection>;
    fishingSections->push_back({20, -1, {0x60, 0x60, 0xff, 0xff}});
    fishingSections->push_back({90, -0.1, {0x30, 0x30, 0x00, 0xff}});
    fishingSections->push_back({110, 5, {0x20, 0xff, 0x20, 0xff}});
    fishingSections->push_back({180, -0.1, {0x30, 0x30, 0x00, 0xff}});
    fishingSections->push_back({200, -5, {0x60, 0x60, 0xff, 0xff}});
}

Fish::~Fish(){};

double Fish::getStrength(int tick, double progress, double hook, Rod *rod)
{
    return 1;
}

std::vector<struct FishingSection> *Fish::getFishingSections(int tick, double progress, double hook, Rod *rod)
{
    // (*fishingSections)[1].upperBound = 30 + (progress/100)*70;
    // std::get<0>((*fishingSections)[3])  = 120 + (progress/100)*70;
    return fishingSections;
}


SDL_Texture *Fish::getTexture()
{
    return texture;
}

struct Rarity Fish::getRarity()
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



