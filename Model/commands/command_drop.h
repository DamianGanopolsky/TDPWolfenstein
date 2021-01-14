#ifndef COMMAND_DROP_H
#define COMMAND_DROP_H

#include "../player/player.h"
#include "./../objects/items/bullets/bullet.h"
#include "./../objects/items/keys/key.h"
#include "./../objects/items/weapons/weapon.h"
#include "./../objects/items/corpse/corpse.h"

class CommandDrop {
 public: 
    CommandDrop();
    //bool drop(PlayerInfo &info, Item &item);
    // bullets:
    bool drop(PlayerInfo &info, Bullet &item);
    // key:
    bool drop(PlayerInfo &info, Key &item);
    // weapons:
    bool drop(PlayerInfo &info, Weapon &item);
    // corpse:
    bool drop(PlayerInfo &info, Corpse &item);

};

#endif