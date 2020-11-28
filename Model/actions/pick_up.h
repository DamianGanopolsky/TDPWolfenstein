#ifndef PICK_UP_H_
#define PICK_UP_H_

#include "./../player/player_info.h"

#include "./../objects/items/bullets/bullet.h"
#include "./../objects/items/healers/blood.h"
#include "./../objects/items/healers/kit.h"
#include "./../objects/items/healers/food.h"
#include "./../objects/items/keys/key.h"
#include "./../objects/items/treasures/treasure.h"
#include "./../objects/items/weapons/weapon.h"

class PickUp {
 public:
    PickUp(PlayerInfo &info);
    // bullets:
    bool pickUp(Bullet &item);
    // healers:
    bool pickUp(Food &item);
    bool pickUp(Kit &item);
    bool pickUp(Blood &item);
    // key:
    bool pickUp(Key &item);
    // treasures:
    bool pickUp(Treasure &item);
    // weapons:
    bool pickUp(Weapon &item);
private:
    PlayerInfo info;
};

#endif   // PICK_UP_H_