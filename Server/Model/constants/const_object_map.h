#ifndef CONST_MAPECT_MAP_H_
#define CONST_MAPECT_MAP_H_

enum ObjectsInMap {
    MAP_NONE            = 0,
    MAP_BULLET          = 1,
    MAP_BLOOD           = 2,
    MAP_FOOD            = 4,
    MAP_KIT             = 8,
    MAP_CHEST           = 16,
    MAP_CROSS           = 32,
    MAP_CROWN           = 64,
    MAP_CUP             = 128,
    MAP_CHAIN_CANNON    = 256,
    MAP_GUN             = 512,
    MAP_MACHINE_GUN     = 1024,
    MAP_KNIFE           = 2048,
    MAP_ROCKET_LAUNCHER = 4096,
    MAP_KEY             = 8192,
    MAP_BARREL          = 16384,
    MAP_TABLE           = 32768,
    MAP_WALL            = 65536,
    MAP_STAIN_BLOOD     = 131072,
    MAP_STAIN_WATER     = 262144,
    MAP_DOOR            = 524288,
    MAP_LOCKED_DOOR     = 1048576,
    MAP_PLAYER          = 2097152,
    //MAP_CORPSE

};

#endif    // CONST_MAPECT_MAP_H_