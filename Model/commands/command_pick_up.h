#ifndef COMMAND_PICK_UP_H_
#define COMMAND_PICK_UP_H_

#include "./../player/player.h"

#include "./../objects/items/bullets/bullet.h"
#include "./../objects/items/healers/blood.h"
#include "./../objects/items/healers/kit.h"
#include "./../objects/items/healers/food.h"
#include "./../objects/items/keys/key.h"
#include "./../objects/items/treasures/treasure.h"
#include "./../objects/items/weapons/weapon.h"

class CommandPickUp {
 public:
    CommandPickUp();
    bool pickUp(PlayerInfo &info, Item &item);
    // bullets:
    bool pickUp(PlayerInfo &info, Bullet &item);
    // healers:
    bool pickUp(PlayerInfo &info, Food &item);
    bool pickUp(PlayerInfo &info, Kit &item);
    bool pickUp(PlayerInfo &info, Blood &item);
    // key:
    bool pickUp(PlayerInfo &info, Key &item);
    // treasures:
    bool pickUp(PlayerInfo &info, Treasure &item);
    // weapons:
    bool pickUp(PlayerInfo &info, Weapon &item);

};

#endif   // COMMAND_PICK_UP_H_