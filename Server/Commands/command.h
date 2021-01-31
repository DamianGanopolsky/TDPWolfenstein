#ifndef COMMAND_H
#define COMMAND_H

#include "../../Common/defs.h"
#include "../../Common/socket.h"
#include "../../Model/game.h"
#include "../../Common/protocol.h"

#include "./command_move_up.h"
#include "./command_move_down.h"
#include "./command_move_left.h"
#include "./command_move_right.h"
#include "./command_stop_moving.h"
#include "./command_rotate_right.h"
#include "./command_rotate_left.h"
#include "./command_stop_rotating.h"
#include "./command_attack.h"
#include "./command_receive_attack.h"
#include "./command_open_door.h"
#include "./command_change_weapon.h"

class Command {
    protected:
        const ConnectionId id_caller;
    
    public:
        Command(const ConnectionId id_caller);
        virtual ~Command();

        Command(const Command&) = delete;
        Command& operator=(const Command&) = delete;
        Command(Command&& other) = delete;
        Command& operator=(Command&& other) = delete;

        virtual void run(Game& game) = 0;
        static Command* newCommand(ConnectionId id_caller, uint8_t opcode, Socket& socket);
};

#endif
