#include "Player.h"

Player::Player()
{
    inventory = std::vector<Fish *>();
    money = 100;
}

Player::~Player() {}

void Player::setRod(Rod *rod)
{
    this->rod = rod;
}

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
