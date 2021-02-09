#include "game.h"
#include "./../clients_connected.h"

#define MAX_NUM 999999999

Game::Game(ClientsConnected& clients_connected, Id map_id) : 
                            new_connection_id(1),
                            players(), players_by_name(),
                            players_in_map(),
                            clients_connected(clients_connected),
                            map_id(map_id), map("../Maps/Fortified_6.yaml"),
                            objMap() {
                                //map.printMatrix();
                            }
Game::~Game() {}

//_getPlayerPosition deberia chequear si el yaml establece la posicion en la que el player deberia aparecer o no.

void Game::_notifyMovementEvent(const ConnectionId id, const Response& response) {
    std::cout <<"Game: _notifyMovementEvent()"<< std::endl;
    Notification* notification;
    Player& player = this->players.at(id);
    if (response.success) {
        std::cout <<"Game: succes response"<< std::endl;
        /*Weapon* weapon = player.getInfo().getWeaponEquiped();
        if (weapon == nullptr) {
            std::cout <<"Game: null weapon"<< std::endl;
        }
        std::cout <<"Game: weapon"<< std::endl;
        int gun_type = weapon->getType();*/
        std::cout <<"Game: gun_type"<< std::endl;
        notification = new Event(map_id, MOVEMENT_EV, id, player.getPos().getX(),
                                 player.getPos().getY(), player.getPos().getAngle(),
                                 player.isMoving(), player.isShooting());
        std::cout <<"Game: send event to all"<< std::endl;
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
    Player& player = this->players.at(id);
    if (response.success) {
        switch (event_type) {
            case NEW_PLAYER_EV: {
                std::cout<<"Game: _notifyEvent, new event"<<std::endl;
                notification = new Event(map_id, event_type, id, player.getPos().getX(), player.getPos().getY(),
                                            player.getPos().getAngle(), player.getInfo().getLife(), player.getInfo().getNumResurrection(),
                                            player.getInfo().getTreasure(), player.getInfo().getNumBullets());
                break;
            }
            case MOVEMENT_EV:
            case DELETE_PLAYER_EV: {
                std::cout<<"Game: _notifyEvent, delete_player"<<std::endl;
                notification = new Event(map_id, event_type, id);
            }
            case ATTACK_EV: {
                std::cout<<"Game: _notifyEvent, attack_ev"<<std::endl;
                player.getInfo().reduceBullets(2);
                notification = new Event(map_id, event_type, id, player.isShooting(),
                                            player.getInfo().getNumBullets());
            }
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

Response Game::_canMove(Map& map, Player& player, std::pair<int, int> next_pos) {
    PlayerPosition pos = player.getPos();
    bool changeCell = _changeCell(pos, next_pos);
    if (changeCell) {
        int object_code = map.getObjectPos(next_pos.first, next_pos.second);
        Object* obj = objMap.getObject(object_code);
        Interact interactor;
        Response not_blocking = interactor.interactWith(player, map, obj);
        return not_blocking;
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

bool Game::_interactWith(Player& player, Map map, Object* obj) {
    return true;
}

bool Game::_getPlayerPosition(Id map_id, int init_x, int init_y, Id new_player_id) {
    return true;
}

void Game::_attack(const ConnectionId id) {
    std::cout <<"Game: _attack()"<< std::endl;
    int damage = 0;
    Player& player = this->players.at(id);
    ConnectionId target_id = 0;
    std::cout <<"Game: start _getTargetAttacked"<< std::endl;
    std::pair<ConnectionId, double> result = _getTargetAttacked(id);
    std::cout <<"Game: end _getTargetAttacked"<< std::endl;
    target_id = result.first;
    double distance = result.second;
    std::cout <<"Game: start useWeapon"<< std::endl;
    Response response = player.useWeapon(distance, damage);
    if (id == target_id) {
        _notifyEvent(id, Response(false, CANT_ATTACK_ITSELF_ERROR_MSG), ATTACK_EV);
    } else if (target_id == 0) {
        //deberian bajarse las balas pero no golpear a nadie????
        _notifyEvent(id, Response(true, CANT_ATTACK_UNKNOWN_ID_ERROR_MSG), ATTACK_EV);
    } else if (player.getInfo().getNumBullets() == 0) {
        _notifyEvent(id, Response(false, CANT_ATTACK_WITHOUT_BULLETS_ERROR_MSG), ATTACK_EV);
    } else {
        _notifyEvent(id, response, ATTACK_EV); 
        Player& target = this->players.at(target_id);
        if(response.success && target.getState()->canBeAttacked()){
            _notifyEvent(target_id, target.receiveAttack(damage), BE_ATTACKED_EV);
        }
    }
}

std::pair<ConnectionId, double> Game::_getTargetAttacked(ConnectionId attacker_id) {
    std::cout <<"Game: _getTargetAttacked"<< std::endl;
    std::unordered_map<ConnectionId, std::pair<int, int>>::iterator it;
    std::pair<ConnectionId, double>closer_player =  std::make_pair(0, MAX_NUM);
    for (it = players_in_map.begin(); it != players_in_map.end(); it++) {
        std::cout <<"Game: enter for"<< std::endl;
        if (it->first != attacker_id) {
            std::cout <<"Game: enter if"<< std::endl;
            int x = (players_in_map.at(attacker_id).first - it->second.first);
            int y = (players_in_map.at(attacker_id).second - it->second.second);
            double distance = sqrt( pow(x, 2) + pow(y, 2) ); 
            if (distance < closer_player.second) {
                closer_player.first = it->first;
                closer_player.second = distance;
            }
        }
    }
    return closer_player;
}

void Game::_move(const ConnectionId id) {
    std::cout <<"Game: player is moving"<< std::endl;
    Player& player = this->players.at(id);
    std::pair<int, int> next_pos = player.getPos().getNextPos(player.getPos().getDirection());
    Response can_move = _canMove(map, player, next_pos);
    if (can_move.success && ((can_move.message) !=  NO_ITEM_PICKED_UP_MSG)) {
        std::cout <<"Game: player can move and picked up"<< std::endl;
        player.update();
        players_in_map.at(id) = std::make_pair(player.getPos().getX(), player.getPos().getY());
        _notifyMovementEvent(id, Response(true, SUCCESS_MSG));
        _notifyItemChanged(id, can_move, _getItemOpcode(can_move.message));
    } else if (can_move.success) {
        std::cout <<"Game: player can move"<< std::endl;
        player.update();
        players_in_map.at(id) = std::make_pair(player.getPos().getX(), player.getPos().getY());
        std::cout <<"Game: player updated"<< std::endl;
        _notifyMovementEvent(id, Response(true, SUCCESS_MSG));
        std::cout <<"Game: players notified"<< std::endl;
    } else {
        std::cout <<"Game: player cant move"<< std::endl;
        player.stopMoving();
        _notifyMovementEvent(id, Response(false, CANT_MOVE_ERROR_MSG));
    }
}

const ConnectionId Game::newPlayer() {
    ConnectionId new_player_id = this->new_connection_id;
    ++(this->new_connection_id);
    //del yaml con mapas obtener Id map_id = ...
    //int init_x, init_y;
    //bool has_assigned_position = _getPlayerPosition(map_id, init_x, init_y, new_player_id);
    //if (!has_assigned_position) {
        //this->map.setPlayerPosition(map_id, init_x, init_y, new_player_id);
    //} else {
        //map.setObjectPos(init_x, init_y, MAP_PLAYER);
    //}
    std::string nickname = "hola";
    std::cout <<"Game: adding a new player"<< std::endl;
    this->players.emplace(std::piecewise_construct, 
                std::forward_as_tuple(new_player_id),
                std::forward_as_tuple(100, 100, 2240, 
                                    2240, nickname, new_player_id));
    std::cout <<"Game: new player added"<< std::endl;
    map.setObjectPos(100, 100, MAP_PLAYER);
    //de alguna manera me tienen que pasar el nickname
    //this->players_by_name[nickname] = new_player_id;
    this->players_in_map.emplace(new_player_id, std::make_pair(100, 100));
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
    this->players.erase(id);
}

void Game::updatePlayers(const int iteration) {
    //std::cout <<"Game: enter updatePlayers()"<< std::endl;
    std::unordered_map<ConnectionId, Player>::iterator 
        player_it = this->players.begin();
    while (player_it != this->players.end()) {
        ConnectionId id = player_it->first;
        Player& player = player_it->second;
        
        if (player.isMoving()) {
            _move(id);
        }
        
        if (player.isRotating()) {
            std::cout <<"Game: player can rotate"<< std::endl;
            player.update();
            _notifyMovementEvent(id, Response(true, SUCCESS_MSG));
        }

        if (player.isShooting()) {
            std::cout <<"Game: player shoot"<< std::endl;
            _attack(id);
        }

        ++player_it;
    }
}

void Game::updateOpenDoorsLifetime(const int iteration) {}

void Game::startMovingUp(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.startMovingUp();
    //_notifyResponse(id, player.startMovingUp());
}

void Game::startMovingDown(const ConnectionId id) {
    std::cout <<"Game: startMovingDown()"<< std::endl;
    Player& player = this->players.at(id);
    player.startMovingDown();
    //_notifyResponse(id, player.startMovingDown());
}

void Game::startMovingLeft(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.startMovingLeft();
    //_notifyResponse(id, player.startMovingLeft());
}

void Game::startMovingRight(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.startMovingRight();
    //_notifyResponse(id, player.startMovingRight());
}

void Game::stopMoving(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.stopMoving();
    //_notifyResponse(id, player.stopMoving());
}

void Game::startRotatingLeft(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.startRotatingLeft();
    //_notifyResponse(id, player.startRotatingLeft());
}

void Game::startRotatingRight(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.startRotatingRight();
    //_notifyResponse(id, player.startRotatingRight());
}

void Game::stopRotating(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.stopRotating();
    //_notifyResponse(id, player.stopRotating());
}

void Game::startShooting(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.startShooting();
}

void Game::stopShooting(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.stopShooting();
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

void Game::receiveAttack(const ConnectionId id, int& damage) {
    Player& player = this->players.at(id);
    _notifyEvent(id, player.receiveAttack(damage), BE_ATTACKED_EV);
}
