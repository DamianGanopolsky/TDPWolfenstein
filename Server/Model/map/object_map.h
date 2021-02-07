#ifndef OBJECT_MAP_H_
#define OBJECT_MAP_H_

#include <unordered_map>
#include "./../objects/object.h"
#include "./../objects/items/bullets/bullet.h"

#include "./../objects/items/healers/blood.h"
#include "./../objects/items/healers/food.h"
#include "./../objects/items/healers/kit.h"

#include "./../objects/items/keys/key.h"

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
#include "./../objects/scene/non_blocking_objects/floor.h"

#include "./../objects/scene/doors/door.h"
#include "./../objects/scene/doors/locked_door.h"

//#include "./../objects/scene/hidden_objects/secret_passage.h"

class ObjectMap {
   std::unordered_map <int, Object*> map;
   Bullet bullet;
   Blood blood;
   Food food;
   Kit kit;
   Chest chest;
   Crown crown;
   Cup cup;
   Cross cross;
   Key key;
   ChainCannon chain_cannon;
   RocketLauncher rocket_launcher;
   Gun gun;
   Knife knife;
   MachineGun machine_gun;
   Barrel barrel;
   Table table;
   Wall wall;
   StainBlood stain_blood;
   StainWater stain_water;
   Floor floor;
   Door door;
   LockedDoor locked_door;
   void setMap();
   public:
      ObjectMap();
      ~ObjectMap();
      Object* getObject(int code);

};

#endif   // OBJECT_MAP_H_
