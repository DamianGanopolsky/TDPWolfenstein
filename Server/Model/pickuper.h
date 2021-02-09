#ifndef PICKUPER_H_
#define PICKUPER_H_

#include "./player/player.h"

#include "../../Common/protocol.h"

#include "./objects/items/bullets/bullet.h"
#include "./objects/items/healers/blood.h"
#include "./objects/items/healers/kit.h"
#include "./objects/items/healers/food.h"
#include "./objects/items/keys/key.h"
#include "./objects/items/treasures/treasure.h"
#include "./objects/items/weapons/weapon.h"

class PickUp {
 public:
    PickUp();
    ~PickUp();
    int pickUp(Player& player, Item* item);
    // bullets:
    /*int pickUp(PlayerInfo &info, Bullet &item);
    // healers:
    int pickUp(PlayerInfo &info, Food &item);
    int pickUp(PlayerInfo &info, Kit &item);
    int pickUp(PlayerInfo &info, Blood &item);
    // key:
    int pickUp(PlayerInfo &info, Key &item);
    // treasures:
    int pickUp(PlayerInfo &info, Treasure &item);
    // weapons:
    int pickUp(PlayerInfo &info, Weapon* item);*/

};

#endif   // PICKUPER_H_