#ifndef INTERACTOR_H_
#define INTERACTOR_H_

#include "./player.h"
#include "./pickuper.h"

#include "./../objects/object.h"
#include "./../objects/items/item.h"
#include "./../objects/scene/blocking_objects/blocking_object.h"
#include "./../objects/scene/non_blocking_objects/non_blocking_object.h"
#include "./../objects/scene/doors/door.h"
#include "./../objects/scene/doors/locked_door.h"
#include "./../objects/scene/hidden_objects/secret_passage.h"

#include <set>

class Interact {
 public:
  Interact();
  bool interactWith(Player &player, int **map, BlockingObject &blocker);
  bool interactWith(Player &player, int **map, NonBlockingObject &blocker);
  bool interactWith(Player &player, int **map, SecretPassage &SecretPassage);
  bool interactWith(Player &player, int **map, Item &item);
  bool interactWith(Player &player, int **map, Object &object);
};

# endif    // INTERACTOR_H_