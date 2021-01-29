#include "game.h"


Game::Game(ClientsConnected& clients_connected) : clients_connected(clients_connected) {}
Game::~Game() {}

//_getPlayerPosition deberia chequear si el yaml establece la posicion en la que el player deberia aparecer o no.
void Game::_notifyResponse(const Id id, const Response& response) {
    MessageOpcode message_opcode;
    if (response.success) {
        message_opcode = SUCCESS_MSSG;
    } else {
        message_opcode = ERROR_MSSG;
    } 
    Notification* message = new Message(message_opcode, response.message);
    //this->clients_connected.notifyAll(id, message);????????
    //this->clients_connected.sendEventToAll(new Event()?????????);
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

void Game::updatePlayers() {}

void Game::updateOpenDoorsLifetime() {}

void Game::startMovingUp(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.moveUp());
}

void Game::startMovingDown(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.moveDown());
}

void Game::startMovingLeft(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.moveLeft());
}

void Game::startMovingRight(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.moveRight());
}

void Game::stopMoving(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.stopMoving());
}

void Game::startRotatingLeft(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.rotateLeft());
}

void Game::startRotatingRight(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.rotateRight());
}

void Game::stopRotating(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.stopRotating());
}

void Game::openDoor(const ConnectionId id) {
    Player& player = this->players.at(id);
    PlayerPosition pos = player.getPos();

    int object_code = map[pos.getX()][pos.getY()];
    Object obj = objMap.getObject(object_code);

    bool door_opened = _interactWith(player, map, obj);
    if (!door_opened) {
        _notifyResponse(id, Response(false, NO_KEY_TO_OPEN_CLOSED_DOOR));
    } else {
        _notifyResponse(id, Response(true, SUCCESS_MSG));
    }
}

void Game::changeWeapon(const ConnectionId id, Weapon weapon) {
    Player& player = this->players.at(id);
    std::list<Weapon> inventory = player.getInfo().getInventory();
    std::list<Weapon>::iterator it;

    it = find(inventory.begin(), inventory.end(), weapon);
    if (it == inventory.end()) {
        _notifyResponse(id, Response(false, NO_WEAPON_IN_INVENTORY_ERROR_MSG));
    } else {
        player.changeWeapon(*it);
        _notifyResponse(id, Response(true, SUCCESS_MSG));
    }
}

void Game::attack(const ConnectionId id, const ConnectionId id_target) {
    int damage = 0;
    Player& player = this->players.at(id);
    Player& target = this->players.at(id_target);
    if (!player.getState()->attack()) {
        _notifyResponse(id, Response(false, STATE_CANT_ATTACK_ERROR_MSG));
    } else {
        _notifyResponse(id, player.useWeapon(id, id_target, &target, damage));
    }
}

void Game::receiveAttack(const ConnectionId id, int& damage) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.receiveAttack(damage));
}
