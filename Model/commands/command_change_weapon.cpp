#include "command_change_weapon.h"
#include <algorithm>

CommandChangeWeapon::CommandChangeWeapon() {}

Response CommandChangeWeapon::run(Player &player, int **map, int command) {
    std::list<Weapon> inventory = player.getInfo().getInventory();
    std::list<Weapon>::iterator it;
    switch (command) {
        case COMMAND_CHANGE_WEAPON_TO_KNIFE: {
            Knife weapon;// = player.getInfo().getWeaponEquiped();
            it = find(inventory.begin(), inventory.end(), weapon);
            if (it == inventory.end()) {
                return Response(false, NO_KNIFE_IN_INVENTORY_ERROR_MSG);
            }
            player.changeWeapon(*it);
            return Response(true, SUCCESS_MSG);
        }
        case COMMAND_CHANGE_WEAPON_TO_GUN: {
            Gun weapon;// = player.getInfo().getWeaponEquiped();
            it = find(inventory.begin(), inventory.end(), weapon);
            if (it == inventory.end()) {
                return Response(false, NO_GUN_IN_INVENTORY_ERROR_MSG);
            }
            player.changeWeapon(*it);
            return Response(true, SUCCESS_MSG);
        }
        case COMMAND_CHANGE_WEAPON_TO_MACHINE_GUN: {
            MachineGun weapon;// = player.getInfo().getWeaponEquiped();
            it = find(inventory.begin(), inventory.end(), weapon);
            if (it == inventory.end()) {
                return Response(false, NO_MACHINE_GUN_IN_INVENTORY_ERROR_MSG);
            }
            player.changeWeapon(*it);
            return Response(true, SUCCESS_MSG);
        }
        case COMMAND_CHANGE_WEAPON_TO_CHAIN_CANNON: {
            ChainCannon weapon;// = player.getInfo().getWeaponEquiped();
            it = find(inventory.begin(), inventory.end(), weapon);
            if (it == inventory.end()) {
                return Response(false, NO_CHAIN_CANNON_IN_INVENTORY_ERROR_MSG);
            }
            player.changeWeapon(*it);
            return Response(true, SUCCESS_MSG);
        }
    }
}