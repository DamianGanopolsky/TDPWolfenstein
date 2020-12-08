#include "./command_attack.h"
#include "./../player/player_state.h"

Response CommandAttack::run(Player* player, Player* target, int command) {
    int damage = 0;
    // Verificamos si puede atacar en su estado
    if (!player->getState()->attack()) {
        return Response(false, STATE_CANT_ATTACK_ERROR_MSG);
    }
    Response response = _useWeapon(player, target, damage);
    return response;
}

Response CommandAttack::_useWeapon(Player* player, Player* target, int& damage) {
    //Chequeamos que no se danie a si mismo
    if (player == target) {
        Response(false, CANT_ATTACK_ITSELF_ERROR_MSG);
    }
    //Verificamos que el target sea atacable
    if (!target->getState()->canBeAttacked()) {
        Response(false, CANT_BE_ATTACKED_ERROR_MSG);
    }
    // Obtenemos el danio del arma.
    Weapon weapon = player->getInfo().getWeaponEquiped();
    damage = weapon.attack(damage);
    // El atacado recibe el daño del ataque.
    target->receiveAttack(damage);
    return Response(true, SUCCESS_MSG);
}