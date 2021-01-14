#ifndef MOVE_H_
#define MOVE_H_

#include "./../player/player.h"
#include "./../objects/items/item.h"
#include "./command_interact.h"
#include "./object_map.h"

#include <unordered_map>
#include <set>
#include <utility>

class CommandMove {
 public:
   CommandMove();
   void run(Player &player, int *map[], int command);
 private:
  ObjectMap objMap; 
  CommandInteract interactor;
  void move(PlayerPosition &pos, int command);
  std::pair<int, int> getNextPos(PlayerPosition &pos, int command);
  bool changeCell(PlayerPosition &pos, std::pair<int, int> &next_pos);
};

# endif    // MOVE_H_