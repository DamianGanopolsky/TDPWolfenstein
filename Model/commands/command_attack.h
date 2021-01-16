#ifndef COMMAND_ATTACK_H
#define COMMAND_ATTACK_H

#include "../player/player.h"

class CommandAttack {
 public: 
    Response run(Player* player, Player* target, int *map[], int command);
 private:
    Bullet bullet;
    Key key;
    Corpse corpse;
    Response _useWeapon(Player* player, Player* target, int& damage);

};

#endif