#ifndef INTERACT_H_
#define INTERACT_H_

#include "./../player/player_info.h"
#include "./../objects/items/item.h"
#include "./../objects/scene/blocking_objects/blocking_object.h"
#include "./../objects/scene/non_blocking_objects/non_blocking_object.h"
#include "./../objects/scene/doors/door.h"
#include "./../objects/scene/doors/locked_door.h"
#include "./../objects/scene/hidden_objects/secret_passage.h"
#include "./../enemies/enemy.h"

#include "./pick_up.h"

#include <set>
#include "./../objects/items/weapons/weapon.h"

class Interact {
 public:
   Interact(PlayerInfo &info);
   bool interactWith(BlockingObject &blocker);
   bool interactWith(NonBlockingObject &blocker);
   bool interactWith(Door &door);
   bool interactWith(LockedDoor &door);
   bool interactWith(SecretPassage &SecretPassage);
   bool interactWith(Item &item);
   bool interactWith(Enemy &enemy);

 private:
    PlayerInfo info;
    PickUp pickuper;
};

# endif    // INTERACT_H_