#include "game.h"
#include "./../clients_connected.h"


Game::Game(ClientsConnected& clients_connected, Id map_id) : 
                            new_connection_id(0),
                            clients_connected(clients_connected), 
                            map_id(map_id), objMap() {}
Game::~Game() {}

//_getPlayerPosition deberia chequear si el yaml establece la posicion en la que el player deberia aparecer o no.

void Game::_notifyMovementEvent(const ConnectionId id, const Response& response) {
    Notification* notification;
    Player& player = this->players.at(id);
    if (response.success) {
        notification = new Event(map_id, MOVEMENT_EV, id, player.getPos().getX(),
                                 player.getPos().getY(), player.getPos().getAngle(),
                                 player.isMoving(), player.isShooting());
        this->clients_connected.sendEventToAll(notification);
    } else {
        notification = new Message(ERROR_MSSG, response.message);
        this->clients_connected.sendMessageToAll(notification);
    } 
}

void Game::_notifyResponse(const ConnectionId id, const Response& response) {
    if(response.success){
        this->clients_connected.sendMessageToAll(new Message(SUCCESS_MSSG, response.message));
    } else {
        this->clients_connected.sendMessageToAll(new Message(ERROR_MSSG, response.message));
    }
}
void Game::_notifyEvent(const ConnectionId id, const Response& response, EventOpcode event_type) {
    Notification* notification;
    std::cout<<"Game: _notifyEvent"<<std::endl;
    Player& player = this->players.at(id);
    std::cout<<"Game: _notifyEvent 1"<<std::endl;
    if (response.success) {
        std::cout<<"Game: _notifyEvent 2"<<std::endl;
        switch (event_type) {
            case NEW_PLAYER_EV: {
                std::cout<<"Game: _notifyEvent, new event"<<std::endl;
                notification = new Event(map_id, event_type, id, player.getPos().getX(), player.getPos().getY(),
                                            player.getPos().getAngle(), player.getInfo().getLife(), player.getInfo().getNumResurrection(),
                                            player.getInfo().getTreasure(), player.getInfo().getNumBullets());
                break;
            }
            case MOVEMENT_EV:
            case DELETE_PLAYER_EV:
            case ATTACK_EV:
            case BE_ATTACKED_EV:
            case RESURRECT_EV:
            case DEATH_EV:
            case CHANGE_WEAPON_EV:{
                break;
            }

        }
        std::cout<<"Game: Se notifica a todos"<<std::endl;
        this->clients_connected.sendEventToAll(notification);
    } else {
        notification = new Message(ERROR_MSSG, response.message);
        this->clients_connected.sendMessageToAll(notification);
    } 
    player.getInfo();
}

void Game::_notifyItemChanged(const ConnectionId id, const Response& response, ItemOpcode item_type) {
    Notification* notification;
    Player& player = this->players.at(id);
    if (response.success) {
        switch (item_type) {
            case CLOSE_DOOR_ITM:
            case OPEN_DOOR_ITM:
            case WEAPON_TAKEN_ITM:
                notification = new ItemChanged(map_id, item_type, id,
                                player.getPos().getX(), player.getPos().getY());
                break;
            case MEDICAL_KIT_TAKEN_ITM:
            case FOOD_TAKEN_ITM:
            case BLOOD_TAKEN_ITM: { 
                notification = new ItemChanged(map_id, item_type, id,
                                player.getPos().getX(), player.getPos().getY(),
                                player.getInfo().getLife());
                break;
            }
            case KEY_TAKEN_ITM: { 
                notification = new ItemChanged(map_id, item_type, id,
                                player.getPos().getX(), player.getPos().getY(),
                                player.getInfo().getKey());
                break;
            }
            case TREASURE_TAKEN_ITM: { 
                notification = new ItemChanged(map_id, item_type, id,
                                player.getPos().getX(), player.getPos().getY(),
                                player.getInfo().getTreasure());
                break;
            }
            case BULLETS_TAKEN_ITM: { 
                notification = new ItemChanged(map_id, item_type, id,
                                player.getPos().getX(), player.getPos().getY(),
                                player.getInfo().getNumBullets());
                break;
            }
            default:
                throw Exception("Unknown item type.");
                break;
        }
        this->clients_connected.sendEventToAll(notification);
    } else {
        notification = new Message(ERROR_MSSG, response.message);
        this->clients_connected.sendMessageToAll(notification);
    } 
}

Response Game::_canMove(int** map, Player& player, std::pair<int, int> next_pos) {
    PlayerPosition pos = player.getPos();
    bool changeCell = _changeCell(pos, next_pos);
    if (changeCell) {
        /*int object_code = map[next_pos.first][next_pos.second];
        Object obj = objMap.getObject(object_code);
        Interact interactor;
        Response not_blocking = interactor.interactWith(player, map, obj);
        return not_blocking;*/
    } else { //se mueve dentro de la misma celda
        return Response(true, NO_ITEM_PICKED_UP_MSG);
    }
    //esto no va
    return Response(true, NO_ITEM_PICKED_UP_MSG);
}

bool Game::_changeCell(PlayerPosition &pos, std::pair<int, int> &next_pos) {
    int current_x = pos.getX();
    int current_y = pos.getY();
    int next_x = next_pos.first;
    int next_y = next_pos.second;
    float value_x = abs((current_x/POINTS_PER_CELL)-(next_x/POINTS_PER_CELL));
    float value_y = abs((current_y/POINTS_PER_CELL)-(next_y/POINTS_PER_CELL));
    if (value_x >= 1 || value_y >= 1) {
        return true;
    }
    return false;
}
ItemOpcode Game::_getItemOpcode(std::string message) {
    return CLOSE_DOOR_ITM;
}

bool Game::_interactWith(Player& player, int** map, Object obj) {
    return true;
}

bool Game::_getPlayerPosition(Id map_id, int init_x, int init_y, Id new_player_id) {
    return true;
}

const ConnectionId Game::newPlayer() {
    ConnectionId new_player_id = this->new_connection_id;
    ++(this->new_connection_id);
    //del yaml con mapas obtener Id map_id = ...
    //int init_x, init_y;
    //bool has_assigned_position = _getPlayerPosition(map_id, init_x, init_y, new_player_id);
    //if (!has_assigned_position) {
        //this->maps.setPlayerPosition(map_id, init_x, init_y, new_player_id);
    //}
    std::string nickname = "hola";
    std::cout <<"Game: adding a new player"<< std::endl;
    this->players.emplace(std::piecewise_construct, 
                std::forward_as_tuple(new_player_id),
                std::forward_as_tuple(100, 100, 2240, 
                                    2240, nickname, new_player_id));
    std::cout <<"Game: new player added"<< std::endl;
    //de alguna manera me tienen que pasar el nickname
    //this->players_by_name[nickname] = new_player_id;
    return new_player_id;

}
void Game::notifyNewPlayer(const ConnectionId id) {
    std::cout <<"Game: new player notified"<< std::endl;
    _notifyEvent(id, Response(true, SUCCESS_MSG), NEW_PLAYER_EV);
}

void Game::deletePlayer(const ConnectionId id) {
    if (!this->players.count(id)) {
        throw Exception("Error in deletePLayer: unknown player id");
    }
    Player& player = players.at(id);
    this->players_by_name.erase(player.getNickname());
    _notifyEvent(id, Response(true, SUCCESS_MSG), DELETE_PLAYER_EV);
    //this->clients_connected.sendEventToAll(new Event()?????????);
    this->players.erase(id);
}

void Game::updatePlayers(const int iteration) {
    std::unordered_map<ConnectionId, Player>::iterator 
        player_it = this->players.begin();
    while (player_it != this->players.end()) {
        ConnectionId id = player_it->first;
        Player& player = player_it->second;
        _notifyResponse(id, player.update(iteration));
        ++player_it;
    }
}

void Game::updateOpenDoorsLifetime(const int iteration) {}

void Game::startMovingUp(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.startMovingUp());
}

void Game::startMovingDown(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.startMovingDown());
}

void Game::startMovingLeft(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.startMovingLeft());
}

void Game::startMovingRight(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.startMovingRight());
}

void Game::stopMoving(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.stopMoving());
}

void Game::startRotatingLeft(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.startRotatingLeft());
}

void Game::startRotatingRight(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.startRotatingRight());
}

void Game::stopRotating(const ConnectionId id) {
    Player& player = this->players.at(id);
    _notifyResponse(id, player.stopRotating());
}

void Game::openDoor(const ConnectionId id) {
    Player& player = this->players.at(id);
    PlayerPosition pos = player.getPos();

    /*int object_code = map[pos.getX()][pos.getY()];
    Object obj = objMap.getObject(object_code);

    bool door_opened = _interactWith(player, map, obj);
    if (!door_opened) {
        _notifyItemChanged(id, Response(false, NO_KEY_TO_OPEN_CLOSED_DOOR), OPEN_DOOR_ITM);
    } else {
        _notifyItemChanged(id, Response(true, SUCCESS_MSG), OPEN_DOOR_ITM);
    }*/
}

void Game::changeWeapon(const ConnectionId id, Weapon* weapon) {
    Player& player = this->players.at(id);
    std::list<Weapon*> inventory = player.getInfo().getInventory();
    std::list<Weapon*>::iterator it;

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
