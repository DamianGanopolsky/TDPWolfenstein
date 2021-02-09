#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <string>
#include <algorithm>

class ClientsConnected;
#include "./../Notifications/event.h"
#include "./../Notifications/item_changed.h"
#include "./../Notifications/message.h"
#include "../../Common/defs.h"
#include "./map/map.h"
#include "./map/object_map.h"
#include "./constants/const_object_map.h"
#include "./player/player.h"
//#include "./objects/items/weapons/weapon.h"
#include "./interactor.h"
#include "./droper.h"

class Game {
    ConnectionId new_connection_id;
    std::unordered_map<ConnectionId, Player> players;
    std::unordered_map<std::string, ConnectionId> players_by_name;
    std::unordered_map<ConnectionId, std::pair<int, int>> players_in_map;
    ClientsConnected& clients_connected;
    Id map_id;
    Map map;
    ObjectMap objMap;

    void _notifyEvent(const ConnectionId id, const Response& response, EventOpcode event_type);
    void _notifyResponse(const ConnectionId id, const Response& response);
    void _notifyItemChanged(const ConnectionId id, const Response& response, ItemOpcode item_type);
    void _notifyMovementEvent(const ConnectionId id, const Response& response);
    Response _canMove(Map& map, Player& player, std::pair<int, int> next_pos);
    bool _changeCell(PlayerPosition &pos, std::pair<int, int> &next_pos);
    //ItemOpcode _getItemOpcode(const char* message); ///falta implmentar
    bool _interactWith(Player& player, Map map, Object* obj);///falta implmentar
    bool _getPlayerPosition(Id map_id, int init_x, int init_y, Id new_player_id);///falta implmentar
    void _attack(const ConnectionId id);
    std::pair<ConnectionId, double> _getTargetAttacked(ConnectionId attacker_id);
    void _move(const ConnectionId id);

    public:
        Game(ClientsConnected& clients_connected, Id map_id);
        ~Game();

        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        Game(Game&& other) = delete;
        Game& operator=(Game&& other) = delete;

        const ConnectionId newPlayer();
        void notifyNewPlayer(const ConnectionId id);
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
        void startShooting(const ConnectionId id);
        void stopShooting(const ConnectionId id);
        void openDoor(const ConnectionId id);
        void changeWeapon(const ConnectionId id, Weapon* weapon);
        void receiveAttack(const ConnectionId, int& damage);


};

#endif