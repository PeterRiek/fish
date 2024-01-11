#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Boat.h"
#include "Rod.h"
#include "Fish.h"

class Player
{
public:
    Player();
    ~Player();

    double getMoney();
    Boat *getBoat();
    Rod *getRod();
    std::vector<Fish *> getInventory();

private:
    double money;
    Boat *boat;
    Rod *rod;
    std::vector<Fish *> inventory;
};