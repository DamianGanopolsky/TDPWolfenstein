# include "player.h"

Player::Player(PlayerInfo &info, PlayerPosition &pos) {
    this->info = info;
    this->pos = pos;
}

PlayerPosition Player::getPos() {
    return this->pos;
}

PlayerInfo Player::getInfo() {
    return this->info;
}

State* Player::getState() {
    return this->state;
}

Race Player::getRace() {
    return this->race;
}

/*
Response Player::_useWeapon(Player* target, int& damage) {
    //Chequeamos que no se danie a si mismo
    if (this == target) {
        Response(false, CANT_ATTACK_ITSELF_ERROR_MSG);
    }
    //Verificamos que el target sea atacable
    if (!target->state->canBeAttacked()) {
        Response(false, CANT_BE_ATTACKED_ERROR_MSG);
    }
    // Obtenemos el danio del arma.
    Weapon weapon = this->info.getWeaponEquiped();
    damage = weapon.attack(damage);
    // Deberiamos chequear si el ataque es mortal??
    // El atacado recibe el daño del ataque.
    target->receiveAttack(damage);
    return Response(true, SUCCESS_MSG);
}

Response Player::useWeapon(Player* target, int& damage) {
    // Verificamos si puede atacar en su estado
    if (!this->state->attack()) {
        return Response(false, STATE_CANT_ATTACK_ERROR_MSG);
    }
    return _useWeapon(target, damage);
}
*/
void Player::receiveAttack(int& damage) {
    if (this->info.getLife() == 0) {
        this->die();
    }
    this->info.reduceLife(damage);
    if (this->info.getLife() == 0) {
        this->die();
    }
}

void Player::die() {
    delete this->state;
    this->state = new Dead(this->player_id);
    //drop items
}

Response Player::resurrect() {
    if(!this->state->resurrect()) {
        return Response(false, STATE_CANT_RESURRECT_ERROR_MSG);
    } else if (this->info.getNumResurrection() == MAX_RESURRECTIONS) {
       return Response(false, MAX_RESURRECTIONS_REACHED_ERROR_MSG); 
    }
    delete this->state;
    this->state = new Alive(this->player_id);
    //poner todos los valores iniciales de vida, balas, etc
}

void Player::changeWeapon(Weapon& weapon) {
    this->info.changeWeaponEquiped(weapon);
    int weapon_type = weapon.getType();
    if (weapon_type == GUN_TYPE) {
        this->race = GUARD;
    } else if (weapon_type == MACHINE_GUN_TYPE) {
        this->race = SS;
    } else if (weapon_type == CHAIN_CANNON_TYPE) {
        this->race = OFFICIAL;
    }
}