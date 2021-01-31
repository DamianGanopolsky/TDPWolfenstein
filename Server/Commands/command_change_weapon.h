#ifndef COMMAND_CHANGE_WEAPON_H
#define COMMAND_CHANGE_WEAPON_H

#include "command.h"
#include "../../Model/objects/items/weapons/weapon.h"

class CommandChangeWeapon : public Command {
    Weapon weapon;
    public:
        CommandChangeWeapon(ConnectionId id_caller, Weapon& weapon);
        ~CommandChangeWeapon();
        void run(Game& game) override;
};

#endif