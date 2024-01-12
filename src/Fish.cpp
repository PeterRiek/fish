#include "Fish.h"

Fish::Fish(SDL_Texture *texture, int rarity, double weight, double size)
{
    this->texture = texture;
    this->rarity = rarity;
    this->weight = weight;
    this->size = size;

    fishingSections = new std::vector<std::tuple<int, double, SDL_Color>>;
    fishingSections->push_back(std::tuple<int, double, SDL_Color>(20, -1, {0x60, 0x60, 0xff, 0xff}));
    fishingSections->push_back(std::tuple<int, double, SDL_Color>(90, -0.1, {0x30, 0x30, 0x00, 0xff}));
    fishingSections->push_back(std::tuple<int, double, SDL_Color>(110, 0.5, {0x20, 0xff, 0x20, 0xff}));
    fishingSections->push_back(std::tuple<int, double, SDL_Color>(180, -0.1, {0x30, 0x30, 0x00, 0xff}));
    fishingSections->push_back(std::tuple<int, double, SDL_Color>(200, -5, {0x60, 0x60, 0xff, 0xff}));
}

Fish::~Fish(){};

double Fish::getStrength(int tick, double progress, double hook, Rod *rod)
{
    return 1;
}

std::vector<std::tuple<int, double, SDL_Color>> *Fish::getFishingSections(int tick, double progress, double hook, Rod *rod)
{
    // std::get<0>((*fishingSections)[1]) = 30 + (progress/100)*70;
    // std::get<0>((*fishingSections)[3])  = 120 + (progress/100)*70;
    return fishingSections;
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



