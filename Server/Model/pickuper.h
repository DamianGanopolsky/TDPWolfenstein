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
#include "./constants/YamlConfig.h"

class PickUp {
 public:
    PickUp();
    ~PickUp();
    int pickUp(Player& player, Item* item);

};

#endif   // PICKUPER_H_