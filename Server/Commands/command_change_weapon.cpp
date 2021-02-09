#include "command_change_weapon.h"

CommandChangeWeapon::CommandChangeWeapon(ConnectionId id_caller,int weapon) : Command(id_caller), weapon(weapon) {}

CommandChangeWeapon::~CommandChangeWeapon() {}

void CommandChangeWeapon::run(Game& game) {
    game.changeWeapon(id_caller, weapon);
}