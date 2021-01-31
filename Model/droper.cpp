#include "./droper.h"
#include "./../constants/const_object_map.h"


Drop::Drop() {}

bool Drop::drop(PlayerInfo &info, Bullet &item) {
    return true;
}

bool Drop::drop(PlayerInfo &info, Key &item) {
    if (info.getKey() == 0) {
        return false;// no keys
    }
    return true;
}

bool Drop::drop(PlayerInfo &info, Weapon &item) {
    //int response;
    if (info.getWeaponEquiped().getType() == GUN_TYPE) {
        return false;// has a gun
    }
    return true;
}

bool Drop::drop(PlayerInfo &info, Corpse &item) {
    return true;
}
