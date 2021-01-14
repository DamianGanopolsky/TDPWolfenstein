#include "./command_attack.h"
#include "command_drop.h"
//#include "./../player/player_state.h"

Response CommandAttack::run(Player* player, Player* target, int *map[], int command) {
    int damage = 0;
    // Verificamos si puede atacar en su estado
    if (!player->getState()->attack()) {
        return Response(false, STATE_CANT_ATTACK_ERROR_MSG);
    }
    Response response = player->useWeapon(target, damage);
    CommandDrop droper;
    if (!target->isAlive()) {
        if (droper.drop(target->getInfo(), target->getInfo().getWeaponEquiped())) {
            //map.addItem(posx, posy, target->getInfo().getWeaponEquiped());
        }
        if (droper.drop(target->getInfo(), bullet)) {
            //map.addItem(posx, posy, bullet);
        }
        if (droper.drop(target->getInfo(), key)) {
            int num_keys = target->getInfo().getKey();
            for (int i = 0; i<= num_keys; i++) {
                //map.addItem(posx, posy, key);
            }
        }
        if (droper.drop(target->getInfo(), corpse)) {
            //map.addItem(posx, posy, corpse);
        }
    }
    return response;
}
