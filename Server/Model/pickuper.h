#ifndef PICKUPER_H_
#define PICKUPER_H_

#include "./player/player.h"

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
    Response pickUp(PlayerInfo &info, Object* item);
    // bullets:
    Response pickUp(PlayerInfo &info, Bullet &item);
    // healers:
    Response pickUp(PlayerInfo &info, Food &item);
    Response pickUp(PlayerInfo &info, Kit &item);
    Response pickUp(PlayerInfo &info, Blood &item);
    // key:
    Response pickUp(PlayerInfo &info, Key &item);
    // treasures:
    Response pickUp(PlayerInfo &info, Treasure &item);
    // weapons:
    Response pickUp(PlayerInfo &info, Weapon* item);

};

#endif   // PICKUPER_H_