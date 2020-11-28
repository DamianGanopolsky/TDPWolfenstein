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
   