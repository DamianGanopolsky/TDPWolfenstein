#include "command_drop.h"
#include "./../constants/const_object_map.h"


CommandDrop::CommandDrop(){}

/*bool CommandDrop::drop(PlayerInfo &info, Item &item) {
    return true;
}*/

bool CommandDrop::drop(PlayerInfo &info, Bullet &item) {
    return true;
}

bool CommandDrop::drop(PlayerInfo &info, Key &item) {
    if (info.getKey() == 0) {
        return false;// no keys
    }
    return true;
}

bool CommandDrop::drop(PlayerInfo &info, Weapon &item) {
    //int response;
    if (info.getWeaponEquiped().getType() == GUN_TYPE) {
        return false;// has a gun
    }
    /*switch (item.getType()) {
        case KNIFE_TYPE:
            response = MAP_KNIFE;
            break;
        case MACHINE_GUN_TYPE:
            response = MAP_MACHINE_GUN;
            break;
        case CHAIN_CANNON_TYPE:
            response = MAP_CHAIN_CANNON;
            break;
        case ROCKET_LAUNCHER_TYPE:
            response = MAP_ROCKET_LAUNCHER;
            break;
        default:
            response = 0;
            break;
    }*/
    return true;
}

bool CommandDrop::drop(PlayerInfo &info, Corpse &item) {
    return true;
}
