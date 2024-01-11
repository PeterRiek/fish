#include "Player.h"

Player::Player() {}

Player::~Player() {}

double Player::getMoney()
{
    return money;
}

Boat *Player::getBoat()
{
    return boat;
}

Rod *Player::getRod()
{
    return rod;
}

std::vector<Fish *> Player::getInventory()
{
    return inventory;
}
