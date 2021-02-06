#ifndef INTERACTOR_H_
#define INTERACTOR_H_

#include "./player/player.h"
#include "pickuper.h"

#include "./objects/object.h"
#include "./objects/items/item.h"
#include "./objects/scene/blocking_objects/blocking_object.h"
#include "./objects/scene/non_blocking_objects/non_blocking_object.h"
//#include "./objects/scene/hidden_objects/secret_passage.h"
#include "./map/map.h"

#include <set>

class Interact {
 public:
  Interact();
  ~Interact();
  Response interactWith(Player &player, Map& map, BlockingObject &blocker);
  Response interactWith(Player &player, Map& map, NonBlockingObject &blocker);
  //Response interactWith(Player &player, Map& map, SecretPassage &SecretPassage);
  Response interactWith(Player &player, Map& map, Item &item);
  Response interactWith(Player &player, Map& map, Object* object);
};

# endif    // INTERACTOR_H_