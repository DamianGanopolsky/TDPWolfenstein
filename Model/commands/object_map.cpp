#include "object_map.h"

#include "./../constants/const_object_map.h"

#include "./../objects/items/bullets/bullet.h"

#include "./../objects/items/healers/blood.h"
#include "./../objects/items/healers/food.h"
#include "./../objects/items/healers/kit.h"

#include "./../objects/items/treasures/chest.h"
#include "./../objects/items/treasures/crown.h"
#include "./../objects/items/treasures/cup.h"
#include "./../objects/items/treasures/cross.h"

#include "./../objects/items/weapons/chain_cannon.h"
#include "./../objects/items/weapons/rocket_launcher.h"
#include "./../objects/items/weapons/gun.h"
#include "./../objects/items/weapons/knife.h"
#include "./../objects/items/weapons/machine_gun.h"

#include "./../objects/scene/blocking_objects/barrel.h"
#include "./../objects/scene/blocking_objects/table.h"
#include "./../objects/scene/blocking_objects/wall.h"

#include "./../objects/scene/non_blocking_objects/stain_blood.h"
#include "./../objects/scene/non_blocking_objects/stain_water.h"

#include "./../objects/scene/doors/door.h"
#include "./../objects/scene/doors/locked_door.h"

#include "./../objects/scene/hidden_objects/secret_passage.h"

ObjectMap::ObjectMap() {
    this->setMap();
}

Object ObjectMap::getObject(int code) {
    return this->map[code];
}

void ObjectMap::setMap() {
    Bullet bullet;
    this->map[MAP_BULLET] = bullet;

    Blood blood;
    this->map[MAP_BLOOD] = blood;
    Food food;
    this->map[MAP_FOOD] = food;
    Kit kit;
    this->map[MAP_KIT] = kit;

    Chest chest;
    this->map[MAP_CHEST] = chest;
    Crown crown;
    this->map[MAP_CROWN] = crown;
    Cup cup;
    this->map[MAP_CUP] = cup;
    Cross cross;
    this->map[MAP_CROSS] = cross;

    ChainCannon chain_cannon;
    this->map[MAP_CHAIN_CANNON] = chain_cannon;
    RocketLauncher rocket_launcher;
    this->map[MAP_ROCKET_LAUNCHER] = rocket_launcher;
    Gun gun;
    this->map[MAP_GUN] = gun;
    Knife knife;
    this->map[MAP_KNIFE] = knife;
    MachineGun machine_gun;
    this->map[MAP_MACHINE_GUN] = machine_gun;

    Barrel barrel;
    this->map[MAP_BARREL] = barrel;
    Table table;
    this->map[MAP_TABLE] = table;
    Wall wall;
    this->map[MAP_WALL] = wall;

    StainBlood stain_blood;
    this->map[MAP_STAIN_BLOOD] = stain_blood;
    StainWater stain_water;
    this->map[MAP_STAIN_WATER] = stain_water;

    Door door;
    this->map[MAP_DOOR] = door;
    LockedDoor locked_door;
    this->map[MAP_LOCKED_DOOR] = locked_door;
    
    LockedDoor secret_passage;
    this->map[MAP_SECRET_PASSAGE] = secret_passage;
}
