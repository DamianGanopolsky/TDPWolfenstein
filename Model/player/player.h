#ifndef PLAYER_H
#define PLAYER_H

#include "./player_info.h"
#include "./../actions/interact.h"

class Player {
 public:
   Player(PlayerInfo &info);

 private:
    PlayerInfo info;
};

#endif   // PLAYER_H
