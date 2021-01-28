#include "player.h"


Player::Player(PlayerInfo &info, PlayerPosition &pos, std::string& nickname, Id map) {
    this->info = info;
    this->pos = pos;
    this->nickname = nickname;
    this->alive = true;
    this->map = map;
}

bool Player::_move(Id map, std::pair<int, int> next_pos) {
    PlayerPosition pos = this->getPos();
    bool changeCell = _changeCell(pos, next_pos);
    if (changeCell || (next_pos.first == -1 && next_pos.second == -1)) {
        int object_code = map[next_pos.first][next_pos.second];
        Object obj = objMap.getObject(object_code);
        Interact interactor;
        bool not_blocking = interactor.interactWith(this, map, obj);
        if (not_blocking) {
            return true;
        } else {
            return false;
        }
    } else { //se mueve dentro de la misma celda
        return true;
    }
}

bool Player::_changeCell(PlayerPosition &pos, std::pair<int, int> &next_pos) {
    int current_x = pos.getX();
    int current_y = pos.getY();
    int next_x = next_pos.first;
    int next_y = next_pos.second;
    float value_x = abs((current_x/POINTS_PER_CELL)-(next_x/POINTS_PER_CELL));
    float value_y = abs((current_y/POINTS_PER_CELL)-(next_y/POINTS_PER_CELL));
    if (value_x >= 1 || value_y >= 1) {
        return true;
    }
    return false;
}

void Player::_die() {
    delete this->state;
    this->state = new Dead(this->player_id);
    this->alive = false;
    Drop droper;
    /*if (droper.drop(this->info, this->info.getWeaponEquiped())) {
        //map.addItem(posx, posy, target->info.getWeaponEquiped());
    }
    if (droper.drop(this->info, bullet)) {
        //map.addItem(posx, posy, bullet);
    }
    if (droper.drop(this->info, key)) {
        int num_keys = this->info.getKey();
        for (int i = 0; i<= num_keys; i++) {
            //map.addItem(posx, posy, key);
        }
    }
    if (droper.drop(this->info, corpse)) {
        //map.addItem(posx, posy, corpse);
    }*/
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

std::string Player::getNickname() {
    return this->nickname;
}

/*Race Player::getRace() {
    return this->race;
}*/

bool Player::isAlive() {
    return this->alive;
}

Response Player::moveUp() {
    std::pair<int, int> next_pos = this->getPos().getPosUp();
    bool can_move = _move(this->map, next_pos);
    if (can_move) {
        this->getPos().moveUp();
        return Response(true, SUCCESS_MSG);
    }
    return Response(false, CANT_MOVE_UP_ERROR_MSG);
}

Response Player::moveDown() {
    std::pair<int, int> next_pos = this->getPos().getPosDown();
    bool can_move = _move(this->map, next_pos);
    if (can_move) {
        this->getPos().moveDown();
        return Response(true, SUCCESS_MSG);
    }
    return Response(false, CANT_MOVE_DOWN_ERROR_MSG);
}

Response Player::moveRight() {
    std::pair<int, int> next_pos = this->getPos().getPosRight();
    bool can_move = _move(this->map, next_pos);
    if (can_move) {
        this->getPos().moveRight();
        return Response(true, SUCCESS_MSG);
    }
    return Response(false, CANT_MOVE_RIGHT_ERROR_MSG);
}

Response Player::moveLeft() {
    std::pair<int, int> next_pos = this->getPos().getPosLeft();
    bool can_move = _move(this->map, next_pos);
    if (can_move) {
        this->getPos().moveLeft();
        return Response(true, SUCCESS_MSG);
    }
    return Response(false, CANT_MOVE_LEFT_ERROR_MSG);
}

Response Player::stopMoving() {
    
}

Response Player::rotateLeft() {
    this->getPos().rotateLeft();
    return Response(true, SUCCESS_MSG);
}

Response Player::rotateRight() {
    this->getPos().rotateRight();
    return Response(true, SUCCESS_MSG);
}

Response Player::stopRotating() {
    
}

Response Player::useWeapon(Id id, Id id_target, Player* target, int& damage) {
    if (this == target) {
        Response(false, CANT_ATTACK_ITSELF_ERROR_MSG);
    }
    if (!target->getState()->canBeAttacked()) {
        Response(false, CANT_BE_ATTACKED_ERROR_MSG);
    }
    Weapon weapon = this->getInfo().getWeaponEquiped();
    damage = weapon.attack(damage);
    target->receiveAttack(damage);
    return Response(true, SUCCESS_MSG);
}

Response Player::receiveAttack(int& damage) {
    this->info.reduceLife(damage);
    if (this->info.getLife() == 0) {
        this->_die();
        return Response(true, PLAYER_DIED_MSG);
    }
    return Response(true, SUCCESS_MSG);
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

Response Player::changeWeapon(Weapon& weapon) {
    if(this->info.hasWeapon(weapon)){
        this->info.changeWeaponEquiped(weapon);
        return Response(true, SUCCESS_MSG);
    }
    return Response(false, NO_WEAPON_IN_INVENTORY_ERROR_MSG);
}