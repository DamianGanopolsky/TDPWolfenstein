#ifndef COMMAND_OPEN_DOOR_H
#define COMMAND_OPEN_DOOR_H

#include "./../player/player.h"
#include "./../objects/object.h"
#include "./object_map.h"
#include "./command_interact.h"
#include "./../objects/scene/doors/door.h"
#include "./../objects/scene/doors/locked_door.h"


class CommandOpenDoor {
 public:
  CommandOpenDoor();
  Response run(Player &player, int **map);
 private:
    ObjectMap objMap; 
    //CommandInteract interacter;
    bool _interactWith(Player &player, int **map, Door &door);
    bool _interactWith(Player &player, int **map, LockedDoor &door);
};

# endif    // INTERACT_H_