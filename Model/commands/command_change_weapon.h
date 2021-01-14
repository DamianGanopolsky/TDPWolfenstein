#ifndef COMMAND_CHANGE_WEAPON_H
#define COMMAND_CHANGE_WEAPON_H

#include "./../player/player.h"
#include "./../constants/const_command.h"
#include "./../objects/items/weapons/knife.h"
#include "./../objects/items/weapons/gun.h"
#include "./../objects/items/weapons/machine_gun.h"
#include "./../objects/items/weapons/chain_cannon.h"


class CommandChangeWeapon {
 public:
    CommandChangeWeapon();
    Response run(Player &player, int **map, int command);
};

#endif      //COMMAND_CHANGE_WEAPON_H