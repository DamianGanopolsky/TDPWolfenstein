#include "player.h"

Player::Player(int width, int height, 
                std::string& nickname, Id id_player, const int& rate) :  
                player_id(id_player), 
                pos(width, height), 
                info(), state(new Alive(id_player)),
                nickname(nickname), alive(true), 
                moving(false), rotating(false), 
                shooting(false), knife(),
                gun(), machine_gun(), chain_cannon(),
                rate(rate), machine_gun_cooldown(0),
                chain_cannon_cooldown(0), gun_can_shoot(true),
                forced_weapon(false), 
                weapon_equiped_before(KNIFE_TYPE) /*default*/ {}

Player::Player(int pos_x, int pos_y, int width, int height,
                std::string& nickname, Id id_player, const int& rate) : 
                player_id(id_player), pos(pos_x, pos_y, width, height), 
                info(), state(new Alive(id_player)),
                nickname(nickname), alive(true), 
                moving(false), rotating(false), 
                shooting(false), knife(),
                gun(), machine_gun(), chain_cannon(),
                rate(rate), machine_gun_cooldown(0),
                chain_cannon_cooldown(0), gun_can_shoot(true),
                forced_weapon(false), 
                weapon_equiped_before(KNIFE_TYPE) /*default*/ {}

Player::~Player() {
    delete this->state;
}

void Player::_die() {
    delete this->state;
    this->state = new Dead(this->player_id);
    this->alive = false;
    //Drop droper;
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

Id Player::getId() {
    return this->player_id;
}

bool Player::isAlive() {
    return this->alive;
}

bool Player::isMoving() {
    return this->moving;
}

bool Player::isRotating() {
    return this->rotating;
}

bool Player::isShooting() {
    return this->shooting;
}

void Player::updateMovement() {
    std::cout <<"Player: updateMovement()"<< std::endl;
    if (this->moving) {
        std::cout <<"Player: is moving"<< std::endl;
        this->pos.move(this->pos.getDirection());
        std::cout <<"Player: updated"<< std::endl;
    }
}

void Player::updateRotation() {
    std::cout <<"Player: updateRotation()"<< std::endl;
    if (this->rotating) {
        this->pos.rotate(this->pos.getRotation());
    }
}

Response Player::updateShooting(double& distance, int& damage, int& iteration) {
    std::cout <<"Player: updateShooting()"<< std::endl;
    if (this->shooting) {
        std::cout <<"Player: is shooting"<< std::endl;
        this->machine_gun_cooldown -= iteration;
        this->chain_cannon_cooldown -= iteration;
        int type = this->info.getWeaponTypeEquiped(); 
        Item* weapon = this->info.getWeaponEquiped();
        if (weapon  == NULL ){std::cout <<"NULL WEAPON"<< std::endl;}
        switch(type) {
            case KNIFE_TYPE: {
                std::cout <<"KNFE ATTACK!"<< std::endl;
                weapon->attack(distance, damage);
                return Response(true, SUCCESS_MSG);
                break;
            }
            case GUN_TYPE: {
                std::cout <<"GUN ATTACK!"<< std::endl;
                std::cout <<"gun_can_shoot value: "<< gun_can_shoot <<std::endl;
                if (this->gun_can_shoot) {
                    std::cout <<"gun can shoot"<< std::endl;
                    if (weapon  == NULL ){std::cout <<"NULL WEAPON"<< std::endl;}
                    weapon->attack(distance, damage);
                    std::cout <<"gun attack"<< std::endl;
                    this->gun_can_shoot = false;
                    return Response(true, SUCCESS_MSG);
                }
                break;
            }
            case MACHINE_GUN_TYPE: {
                std::cout <<"MACHINE GUN ATTACK!"<< std::endl;
                while (this->machine_gun_cooldown <= 0) {
                    this->machine_gun_cooldown += MACHINE_GUN_TIME;
                    //this->machine_gun_cooldown += GameConfig.machine_gun_cooldown;
                    weapon->attack(distance, damage);
                    return Response(true, SUCCESS_MSG);
                }
                break;
            }
            case CHAIN_CANNON_TYPE: {
                std::cout <<"CHAIN CANNON ATTACK!"<< std::endl;
                while (this->chain_cannon_cooldown <= 0) {
                    this->chain_cannon_cooldown += CHAIN_CANNON_TIME;
                    //this->chain_cannon_cooldown += GameConfig.chain_cannon_cooldown;
                    weapon->attack(distance, damage);
                    return Response(true, SUCCESS_MSG);
                }
                break;
            }
        }
        return Response(false, CANT_SHOOT_ERROR_MSG);
    }
    return Response(false, CANT_SHOOT_ERROR_MSG);
}


Response Player::startMovingUp() {
    if (!this->state->canMove()) {
        return Response(false, CANT_MOVE_UP_ERROR_MSG);
    }
    this->pos.changeDirection(UP_DIR);
    this->moving = true;
    return Response(true, SUCCESS_MSG);
}

Response Player::startMovingDown() {
    if (!this->state->canMove()) {
        return Response(false, CANT_MOVE_DOWN_ERROR_MSG);
    }
    this->pos.changeDirection(DOWN_DIR);
    std::cout <<"Player: changed direction"<< std::endl;
    this->moving = true;
    return Response(true, SUCCESS_MSG);
}

Response Player::startMovingRight() {
    if (!this->state->canMove()) {
        return Response(false, CANT_MOVE_RIGHT_ERROR_MSG);
    }
    this->pos.changeDirection(RIGHT_DIR);
    this->moving = true;
    return Response(true, SUCCESS_MSG);
}

Response Player::startMovingLeft() {
    if (!this->state->canMove()) {
        return Response(false, CANT_MOVE_LEFT_ERROR_MSG);
    }
    this->pos.changeDirection(LEFT_DIR);
    this->moving = true;
    return Response(true, SUCCESS_MSG);
}

Response Player::stopMoving() {
    this->moving = false;
    return Response(true, SUCCESS_MSG);
}

Response Player::startRotatingLeft() {
    this->pos.changeRotation(LEFT_ROTATION_DIR);
    this->rotating = true;
    return Response(true, SUCCESS_MSG);
}

Response Player::startRotatingRight() {
    this->pos.changeRotation(RIGHT_ROTATION_DIR);
    this->rotating = true;
    return Response(true, SUCCESS_MSG);
}

Response Player::stopRotating() {
    this->rotating = false;
    return Response(true, SUCCESS_MSG);
}

Response Player::startShooting() {
    if (!this->getState()->attack()) {
        return Response(false, STATE_CANT_ATTACK_ERROR_MSG);
    }
    this->shooting = true;
    return Response(true, SUCCESS_MSG);
}

Response Player::stopShooting() {
    this->shooting = false;
    return Response(true, SUCCESS_MSG);
}

/*Response Player::useWeapon(double& distance, int& damage) {
    //Weapon* weapon = this->getInfo().getWeaponEquiped();
    //weapon->attack(distance, damage);
    return Response(true, SUCCESS_MSG);
}*/

Response Player::receiveAttack(int& damage) {
    this->reduceLife(damage);
    if (this->info.getLife() == 0) {
        this->_die();
        return Response(true, PLAYER_DIED_MSG);
    }
    return Response(true, SUCCESS_MSG);
}

Response Player::resurrect() {
    if(!this->state->resurrect()) {
        return Response(false, STATE_CANT_RESURRECT_ERROR_MSG);
    //} else if (this->info.getNumResurrection() == MAX_RESURRECTIONS) {
    } else if (this->info.getNumResurrection() == GameConfig.max_resurrections) {
       return Response(false, MAX_RESURRECTIONS_REACHED_ERROR_MSG); 
    }
    delete this->state;
    this->state = new Alive(this->player_id);
    addNumResurrection();
    addLife(MAX_LIFE);
    deleteInventory(KNIFE_TYPE);
    deleteInventory(MACHINE_GUN_TYPE);
    deleteInventory(CHAIN_CANNON_TYPE);
    reduceBullets(MAX_BULLETS);
    addBullets(8);
    return Response(true, SUCCESS_MSG);
}

Response Player::changeWeapon(const int& weapon) {
    if(this->info.hasWeapon(weapon)){
        switch (weapon) {
            case KNIFE_TYPE: {
                this->info.changeWeaponEquiped(weapon);
                break;
            }
            case GUN_TYPE: {
                this->info.changeWeaponEquiped(weapon);
                break;
            }
            case MACHINE_GUN_TYPE: {
                this->info.changeWeaponEquiped(weapon);
                break;
            }
            case CHAIN_CANNON_TYPE: {
                this->info.changeWeaponEquiped(weapon);
                break;
            }
            default:
                break;
        }
        return Response(true, SUCCESS_MSG);
    }
    return Response(false, NO_WEAPON_IN_INVENTORY_ERROR_MSG);
}

void Player::addInventory(int weapon) {
    this->info.inventory.push_back(weapon);
}

void Player::deleteInventory(int weapon) {
    this->info.inventory.remove(weapon);
}

void Player::setPosition(int x, int y) {
    this->pos.setPosition(x,y);
}

void Player::addLife(int life) {
    this->info.life += life;
    //this->info.life = (this->info.life > MAX_LIFE) ? MAX_LIFE : this->info.life;
    this->info.life = (this->info.life > GameConfig.max_life) ? GameConfig.max_life : this->info.life;
}

void Player::addBullets(int bullets) {
    this->info.bullets += bullets;
    //this->info.bullets = (this->info.bullets > MAX_BULLETS) ? MAX_BULLETS : this->info.bullets;
    this->info.bullets = (this->info.bullets > GameConfig.max_bullets) ? GameConfig.max_bullets : this->info.bullets;
}

void Player::addNumKeys(int key) {
    this->info.keys += key;
}

void Player::addTreasure(int treasure) {
    this->info.treasure += treasure;
}

void Player::addNumResurrection() {
    this->info.resurrected += 1;
}

void Player::reduceLife(int life) {
    this->info.life -= life;
    this->info.life = (this->info.life < 0) ? 0 : this->info.life;
}

void Player::reduceBullets(int bullets) {
    this->info.bullets -= bullets;
    this->info.bullets = (this->info.bullets < 0) ? 0 : this->info.bullets;
}

void Player::reduceNumKeys(int key) {
    this->info.keys -= key;
    this->info.keys = (this->info.keys < 0) ? 0 : this->info.keys;
}

void Player::reduceTreasure(int treasure) {
    this->info.treasure -= treasure;
    this->info.treasure = (this->info.treasure < 0) ? 0 : this->info.treasure;
}
