#ifndef PLAYER_H
#define PLAYER_H

#include "./player_info.h"
#include "./player_position.h"
#include "./player_state.h"
#include "./def.h"
#include "../response.h"
#include "../constants/config_player.h"

class Player {
 public:
   Player(PlayerInfo &info, PlayerPosition &pos);
   PlayerPosition getPos();
   PlayerInfo getInfo();
   State* getState();
   Race getRace();
   bool isAlive();
   Response useWeapon(Player* target, int& damage);
   void receiveAttack(int& damage);
   void die();
   Response resurrect();
   void changeWeapon(Weapon& weapon);
 private:
    Id player_id;
    PlayerPosition pos;
    PlayerInfo info;
    State* state;
    Race race;
    bool alive;
};

#endif   // PLAYER_H
