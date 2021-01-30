#include "game.h"


Game::Game(ClientsConnected& clients_connected, Id map_id) : 
                            clients_connected(clients_connected), 
                            map_id(map_id) {}
Game::~Game() {}

//_getPlayerPosition deberia chequear si el yaml establece la posicion en la que el player deberia aparecer o no.
void Game::_notifyEvent(const Id id, const Response& response, EventOpcode event_type) {
    Notification* notification;
    if (response.success) {
        notification = new Event(map_id, this->players.at(id), event_type);
        this->clients_connected.sendEventToAll(notification);
    } else {
        notification = new Message(ERROR_MSSG, response.message);
        this->clients_connected.notifyAll(notification);
    } 
}

void Game::_notifyItemChanged(const Id id, const Response& response, ItemOpcode item_type) {
    Notification* notification;
    if (response.success) {
        notification = new ItemChanged(map_id, this->players.at(id), item_type);
        this->clients_connected.sendEventToAll(notification);
    } else {
        notification = new Message(ERROR_MSSG, response.message);
        this->clients_connected.notifyAll(notification);
    } 
}

const ConnectionId Game::newPlayer() {
    Id new_player_id = this->new_connection_id;
    ++this->new_connection_id;
    //del yaml con mapas obtener Id map_id = ...
    int init_x, init_y;
    bool has_assigned_position = _getPlayerPosition(map_id, init_x, init_y, new_player_id);
    if (!has_assigned_position) {
        //this->maps.setPlayerPosition(map_id, init_x, init_y, new_player_id);
    }
    this->players.emplace(std::piecewise_construct, 
                std::forward_as_tuple(new_player_id),
                std::forward_as_tuple(/*poner parametros del constructor del player*/));
    //de alguna manera me tienen que pasar el nickname
    this->players_by_name[nickname] = new_player_id;
    //this->clients_connected.sendEventToAll(new Event()?????????);
    return new_player_id;

}

void Game::deletePlayer(const ConnectionId id) {
    if (!this->players.count(id)) {
        throw Exception("Error in deletePLayer: unknown player id");
    }
    Player& player = players.at(id);
    this->players_by_name.erase(player.getNickname());
    //this->clients_connected.sendEventToAll(new Event()?????????);
    this->players.erase(id);
}

void Game::updatePlayers(const int iteration) {
    std::unordered_map<ConnectionId, Player>::iterator 
        player_it = this->players.begin();
    while (player_it != this->players.end()) {
        ConnectionId id = player_it->first;
        Player& player = player_it->second;
        _notifyEvent(id, player.update(iteration), MOVEMENT_EV);
        ++player_it;
    }
}

void Game::updateOpenDoorsLifetime(const int iteration) {}

void Game::startMovingUp(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyEvent(id, player.moveUp(), MOVEMENT_EV);
}

void Game::startMovingDown(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyEvent(id, player.moveDown(), MOVEMENT_EV);
}

void Game::startMovingLeft(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyEvent(id, player.moveLeft(), MOVEMENT_EV);
}

void Game::startMovingRight(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyEvent(id, player.moveRight(), MOVEMENT_EV);
}

void Game::stopMoving(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyEvent(id, player.stopMoving(), MOVEMENT_EV);
}

void Game::startRotatingLeft(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyEvent(id, player.rotateLeft(), MOVEMENT_EV);
}

void Game::startRotatingRight(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyEvent(id, player.rotateRight(), MOVEMENT_EV);
}

void Game::stopRotating(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyEvent(id, player.stopRotating(), MOVEMENT_EV);
}

void Game::openDoor(const ConnectionId id) {
    Player& player = this->players.at(id);
    PlayerPosition pos = player.getPos();

    int object_code = map[pos.getX()][pos.getY()];
    Object obj = objMap.getObject(object_code);

    bool door_opened = _interactWith(player, map, obj);
    if (!door_opened) {
        _notifyItemChanged(id, Response(false, NO_KEY_TO_OPEN_CLOSED_DOOR), OPEN_DOOR_ITM);
    } else {
        _notifyItemChanged(id, Response(true, SUCCESS_MSG), OPEN_DOOR_ITM);
    }
}

void Game::changeWeapon(const ConnectionId id, Weapon weapon) {
    Player& player = this->players.at(id);
    std::list<Weapon> inventory = player.getInfo().getInventory();
    std::list<Weapon>::iterator it;

    it = find(inventory.begin(), inventory.end(), weapon);
    if (it == inventory.end()) {
        _notifyEvent(id, Response(false, NO_WEAPON_IN_INVENTORY_ERROR_MSG), CHANGE_WEAPON_EV);
    } else {
        player.changeWeapon(*it);
        _notifyEvent(id, Response(true, SUCCESS_MSG), CHANGE_WEAPON_EV);
    }
}

void Game::attack(const ConnectionId id, const ConnectionId id_target) {
    int damage = 0;
    Player& player = this->players.at(id);
    Player& target = this->players.at(id_target);
    if (!player.getState()->attack()) {
        _notifyEvent(id, Response(false, STATE_CANT_ATTACK_ERROR_MSG), ATTACK_EV);
    } else {
        _notifyEvent(id, player.useWeapon(id, id_target, &target, damage), ATTACK_EV);
    }
}

void Game::receiveAttack(const ConnectionId id, int& damage) {
    Player& player = this->players.at(id);
    _notifyEvent(id, player.receiveAttack(damage), BE_ATTACKED_EV);
}
