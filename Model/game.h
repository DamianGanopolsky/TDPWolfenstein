#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <string>
#include <algorithm>

#include "../Server/Notifications/event.h"
#include "../Server/Notifications/item_changed.h"
#include "../Server/Notifications/message.h"
#include "../Common/defs.h"
#include "../Server/clients_connected.h"
#include "./map/object_map.h"
#include "./constants/const_object_map.h"
#include "./player/player.h"
#include "./objects/items/weapons/weapon.h"
#include "./interactor.h"
#include "./droper.h"

class Game {
    ConnectionId new_connection_id;
    std::unordered_map<ConnectionId, Player> players;
    std::unordered_map<std::string, ConnectionId> players_by_name;
    ClientsConnected& clients_connected;
    Id map_id;
    int** map;
    ObjectMap objMap;

    void _notifyEvent(const Id id, const Response& response, EventOpcode event_type);
    void _notifyResponse(const Id id, const Response& response);
    void _notifyItemChanged(const Id id, const Response& response, ItemOpcode item_type);
    void _notifyMovementEvent(const Id id, const Response& response);
    Response _canMove(int** map, Player& player, std::pair<int, int> next_pos);
    bool _changeCell(PlayerPosition &pos, std::pair<int, int> &next_pos);

    public:
        Game(ClientsConnected& clients_connected, Id map_id);
        ~Game();

        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        Game(Game&& other) = delete;
        Game& operator=(Game&& other) = delete;

        const ConnectionId newPlayer();
        void deletePlayer(const ConnectionId id);
        void updatePlayers(const int iteration);

        void updateOpenDoorsLifetime(const int iteration);

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