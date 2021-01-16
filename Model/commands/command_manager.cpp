#include "command_manager.h"

#include "./command_move.h"
#include "./command_attack.h"
#include "./command_open_door.h"
#include "./command_change_weapon.h"

CommandManager::CommandManager() {};

void CommandManager::applyCommand(int command, int** map, Player player, Player target) {
    int command_type = this->identifyCommandType(command);
    switch (command_type) {
        case COMMAND_TYPE_MOVE: {
            CommandMove cmdMove;
            //response = 
            cmdMove.run(player, map, command);
            //return;
            break;
        }
        case COMMAND_TYPE_ATACK: {
            CommandAttack cmdAttack;
            //response = 
            cmdAttack.run(&player, &target, map, command);
            break;
        }
        case COMMAND_TYPE_CHANGE_WEAPON: {
            CommandChangeWeapon cmdChangeWeapon;
            //response =
            cmdChangeWeapon.run(player, map, command);
            //return COMMAND_TYPE_CHANGE_WEAPON;
            break;
        }
        case COMMAND_TYPE_OPEN_DOOR: {
            CommandOpenDoor cmdOpenDoor;
            //response = 
            cmdOpenDoor.run(player, map);
            break;
        }
        case -1: {
            //return Response(false, UNKNOWN_COMMAND_ERROR_MSG);
        }
    }
}

int CommandManager::identifyCommandType(int command) { 
    if(command >= COMMAND_MOVE_RANGE_START && command <= COMMAND_MOVE_RANGE_END) {
        return COMMAND_TYPE_MOVE;
    }
    switch (command) {
        case COMMAND_ATACK: {
            return COMMAND_TYPE_ATACK;
            break;
        }
        case COMMAND_CHANGE_WEAPON_TO_KNIFE: {
            return COMMAND_TYPE_CHANGE_WEAPON;
            break;
        }
        case COMMAND_CHANGE_WEAPON_TO_GUN: {
            return COMMAND_TYPE_CHANGE_WEAPON;
            break;
        }
        case COMMAND_CHANGE_WEAPON_TO_MACHINE_GUN: {
            return COMMAND_TYPE_CHANGE_WEAPON;
            break;
        }
        case COMMAND_CHANGE_WEAPON_TO_CHAIN_CANNON: {
            return COMMAND_TYPE_CHANGE_WEAPON;
            break;
        }
        case COMMAND_OPEN_DOOR: {
            return COMMAND_TYPE_OPEN_DOOR;
            break;
        }
    }
    return -1;
}