#include "object_map.h"
#include <iostream>

#include "./../constants/const_object_map.h"

ObjectMap::ObjectMap() : map(), player(0,0,str,0,0), bullet(), blood(), food(),
                        kit(), chest(), crown(), cup(), cross(),
                        key(), chain_cannon(), rocket_launcher(),
                        gun(), knife(), machine_gun(), barrel(),
                        table(), wall(), stain_blood(),
                        stain_water(), floor(), door(),
                        locked_door() { this->setMap(); }

ObjectMap::~ObjectMap() {}

Object* ObjectMap::getObject(int code) {
    return this->map.at(code);
}

void ObjectMap::setMap() {
    this->map[MAP_PLAYER] = &player;
    
    this->map[MAP_BULLET] = &bullet;

    this->map[MAP_BLOOD] = &blood;
    this->map[MAP_FOOD] = &food;
    this->map[MAP_KIT] = &kit;

    this->map[MAP_CHEST] = &chest;
    this->map[MAP_CROWN] = &crown;
    this->map[MAP_CUP] = &cup;
    this->map[MAP_CROSS] = &cross;

    this->map[MAP_KEY] = &key;

    this->map[MAP_CHAIN_CANNON] = &chain_cannon;
    this->map[MAP_ROCKET_LAUNCHER] = &rocket_launcher;
    this->map[MAP_GUN] = &gun;
    this->map[MAP_KNIFE] = &knife;
    this->map[MAP_MACHINE_GUN] = &machine_gun;

    this->map[MAP_BARREL] = &barrel;
    this->map[MAP_TABLE] = &table;
    this->map[MAP_WALL] = &wall;

    this->map[MAP_STAIN_BLOOD] = &stain_blood;
    this->map[MAP_STAIN_WATER] = &stain_water;
    this->map[MAP_NONE] = &floor;

    this->map[MAP_DOOR] = &door;
    this->map[MAP_LOCKED_DOOR] = &locked_door;
}
