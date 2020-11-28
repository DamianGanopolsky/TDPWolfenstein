#ifndef PLAYER_H
#define PLAYER_H

#include "./player_info.h"
#include "./player_position.h"

class Player {
 public:
   Player(PlayerInfo &info, PlayerPosition &pos);
   PlayerPosition getPos();
   PlayerInfo getInfo();
 private:
    PlayerPosition pos;
    PlayerInfo info;
};

#endif   // PLAYER_H
