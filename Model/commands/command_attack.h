#ifndef COMMAND_ATTACK_H
#define COMMAND_ATTACK_H

#include "../player/player.h"

class CommandAttack {
 public: 
    Response run(Player* player, Player* target, int command);
 private:
    Response _useWeapon(Player* player, Player* target, int& damage);

};

#endif