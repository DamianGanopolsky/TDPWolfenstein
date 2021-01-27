#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <string>
#include <algorithm>

#include "../Common/defs.h"
#include "../Model/player/player.h"
#include "../Model/objects/items/weapons/weapon.h"

class Game {
    ConnectionId new_connection_id;
    std::unordered_map<ConnectionId, Player> players;
    std::unordered_map<std::string, ConnectionId> players_by_name;

    void _notifyResponse(const Id id, const Response& response);

    public:
        Game();
        ~Game();

        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        Game(Game&& other) = delete;
        Game& operator=(Game&& other) = delete;

        const ConnectionId newPlayer();
        void deletePlayer(const ConnectionId id);
        void updatePlayers();

        void updateOpenDoorsLifetime();

        void startMovingUp(const ConnectionId id);
        void startMovingDown(const ConnectionId id);
        void startMovingLeft(const ConnectionId id);
        void startMovingRight(const ConnectionId id);
        void stopMoving(const ConnectionId id);
        void startRotatingLeft(const ConnectionId id);
        void startRotatingRight(const ConnectionId id);
        void stopRotating(const ConnectionId id);
        void openDoor(const ConnectionId id);
        void changeWeapon(const ConnectionId id, Weapon weapon);
        void attack(const ConnectionId id, const ConnectionId id_target);
        void receiveAttack(const ConnectionId, int& damage);


};

#endif