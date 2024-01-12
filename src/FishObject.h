#pragma once

#include "GameObject.h"
#include <vector>
#include <tuple>

class FishObject : public GameObject
{
public:
    FishObject(SDL_Renderer *renderer, const char *imagePath, int x, int y, int width, int height, int strength, std::vector<std::tuple<int, int, SDL_Color>> *sections);
    ~FishObject();

    void update() override;
    void render() override;
    void pull(int pull);

private:
    int strength;
    int hook;
    int progress;
    std::vector<std::tuple<int, int, SDL_Color>> *sections;
    /*
    [
        range = [0;section[0]]
        modifier = section[1];
    ]
    */
};
