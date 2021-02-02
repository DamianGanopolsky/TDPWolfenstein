#include "command_change_weapon.h"

CommandChangeWeapon::CommandChangeWeapon(ConnectionId id_caller, Weapon& weapon) : Command(id_caller), weapon(&weapon) {}

CommandChangeWeapon::~CommandChangeWeapon() {}

void CommandChangeWeapon::run(Game& game) {
    game.changeWeapon(id_caller, weapon);
}