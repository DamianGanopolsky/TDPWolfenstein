#include "player_state.h"

State::State(Id player_id) : player_id(player_id) {}
State::~State() {}

Alive::Alive(Id player_id) : State(player_id) {}
Alive::~Alive() {}
const bool Alive::attack() const {
    return true;
}
const bool Alive::canBeAttacked() const {
    return true;
} 
const bool Alive::resurrect() const {
    return false;
}
const bool Alive::canMove() const {
    return true;
}

Dead::Dead(Id player_id) : State(player_id) {}
Dead::~Dead() {}

const bool Dead::attack() const {
    return false;
}
const bool Dead::canBeAttacked() const {
    return false;
}
const bool Dead::resurrect() const {
    return true;
}
const bool Dead::canMove() const {
    return false;
}