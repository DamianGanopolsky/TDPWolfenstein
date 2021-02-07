#include "command.h"

#include "./command_move_up.h"
#include "./command_move_down.h"
#include "./command_move_left.h"
#include "./command_move_right.h"
#include "./command_stop_moving.h"
#include "./command_rotate_right.h"
#include "./command_rotate_left.h"
#include "./command_stop_rotating.h"
#include "./command_start_shooting.h"
#include "./command_stop_shooting.h"
#include "./command_receive_attack.h"
#include "./command_open_door.h"
#include "./command_change_weapon.h"

#include "./../Model/objects/items/weapons/knife.h"
#include "./../Model/objects/items/weapons/gun.h"
#include "./../Model/objects/items/weapons/machine_gun.h"
#include "./../Model/objects/items/weapons/chain_cannon.h"

Command::Command(const ConnectionId id_caller) : id_caller(id_caller) {}

Command::~Command() {}

Command* Command::newCommand(ConnectionId id_caller, uint8_t opcode, Socket& socket) {
    switch (opcode) {
        case START_MOVING_UP_CMD: {
            return new CommandMoveUp(id_caller);
        }
        case START_MOVING_DOWN_CMD: {
            return new CommandMoveDown(id_caller);
        }
        case START_MOVING_LEFT_CMD: {
            return new CommandMoveLeft(id_caller);
        }
        case START_MOVING_RIGHT_CMD: {
            return new CommandMoveRight(id_caller);
        }
        case STOP_MOVING_CMD: {
            return new CommandStopMoving(id_caller);
        }
        case START_ROTATING_LEFT: {
            return new CommandRotateLeft(id_caller);
        }
        case START_ROTATING_RIGHT: {
            return new CommandRotateRight(id_caller);
        }
        case STOP_ROTATING: {
            return new CommandStopRotating(id_caller);
        }
        case START_SHOOTING_CMD: {
            return new CommandStartShooting(id_caller);
        }
        case STOP_SHOOTING_CMD: {
            return new CommandStopShooting(id_caller);
        }
        /*case RECIEVE_ATTACK_CMD: {
            //socket >> damage;
            return new CommandReceiveAttack(id_caller, damage);
        }*/
        case OPEN_DOOR_CMD: {
            return new CommandOpenDoor(id_caller);
        }
        case CHANGE_WEAPON_TO_KNIFE_CMD: {
            Knife weapon;
            return new CommandChangeWeapon(id_caller, weapon);
        }
        case CHANGE_WEAPON_TO_GUN_CMD: {
            Gun weapon;
            return new CommandChangeWeapon(id_caller, weapon);
        }
        case CHANGE_WEAPON_TO_MACHINE_GUN_CMD: {
            MachineGun weapon;
            return new CommandChangeWeapon(id_caller, weapon);
        }
        case CHANGE_WEAPON_TO_CHAIN_CANNON_CMD: {
            ChainCannon weapon;
            return new CommandChangeWeapon(id_caller, weapon);
        }
        default: {
            throw Exception("Error: Server received an unknown command.");
        }
    }
}
