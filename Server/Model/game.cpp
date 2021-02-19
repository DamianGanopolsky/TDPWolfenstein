#include "game.h"
#include "./../clients_connected.h"

#define MAX_NUM 999999999
#define PATH_TO_MAP "../Maps/"
#define YAML_EXT ".yaml"

Game::Game(ClientsConnected& clients_connected, std::string map_Yaml, int& rate) : 
                            new_connection_id(1),
                            YamlMapName(map_Yaml),
                            players(), players_by_name(),
                            players_in_map(), respawn_positions(),
                            clients_connected(clients_connected),
                            post_game(YamlMapName), map_id(2), 
                            map(PATH_TO_MAP+map_Yaml+YAML_EXT),
                            game_ended(false), objMap(), rate(rate) {}

Game::~Game() {}

void Game::_notifyMovementEvent(const ConnectionId id, const Response& response) {
    std::cout <<"Game: _notifyMovementEvent()"<< std::endl;
    Notification* notification;
    Player& player = this->players.at(id);
    if (response.success) {
        notification = new Event(YamlMapName, MOVEMENT_EV, id, player.getPos().getX(),
                                 player.getPos().getY(), player.getPos().getAngle(),
                                 player.isMoving(), player.isShooting());
        //std::cout <<"Game: send event to all"<< std::endl;
        this->clients_connected.sendEventToAll(notification);
    } else {
        notification = new Message(ERROR_MSSG, response.message);
        this->clients_connected.sendMessageToAll(notification);
    } 
}

void Game::_notifyChangeWeaponEvent(const ConnectionId id, const Response& response, int weapon) {
    std::cout <<"Game: _notifyChangeWeaponEvent()"<< std::endl;
    Notification* notification;
    if (response.success) {
        std::cout <<"Game: weapon"<< weapon <<std::endl;
        notification = new Event(YamlMapName, CHANGE_WEAPON_EV, id, weapon);
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
            case RESURRECT_EV:
            case NEW_PLAYER_EV: {
                std::cout<<"Game: _notifyEvent, new event"<<std::endl;
                notification = new Event(YamlMapName, event_type, id, player.getPos().getX(), player.getPos().getY(),
                                            player.getPos().getAngle(), player.getInfo().getLife(), player.getInfo().getNumResurrection(),
                                            player.getInfo().getTreasure(), player.getInfo().getNumBullets());
                break;
            }
            case DELETE_PLAYER_EV: {
                std::cout<<"Game: _notifyEvent, delete_player"<<std::endl;
                notification = new Event(YamlMapName, event_type, id);
                break;
            }
            case ATTACK_EV: {
                std::cout<<"Game: _notifyEvent, attack_ev"<<std::endl;
                notification = new Event(YamlMapName, event_type, id,
                                        player.getInfo().getNumBullets());
                break;
            }
            case BE_ATTACKED_EV: {
                std::cout<<"Game: _notifyEvent, be_attack_ev"<<std::endl;
                notification = new Event(YamlMapName, event_type, id, player.getInfo().getLife());
                break;
            }
            case DEATH_EV: {
                std::cout<<"Game: _notifyEvent, death_event"<<std::endl;
                notification = new Event(YamlMapName, event_type, id, player.getPos().getX(), player.getPos().getY());
                break;
            }
            case CHANGE_WEAPON_EV:
            case MOVEMENT_EV:
            case SCORES_EV: {
                break;
            }

        }
        std::cout<<"Game: Se notifica a todos"<<std::endl;
        this->clients_connected.sendEventToAll(notification);
    } else {
        notification = new Message(ERROR_MSSG, response.message);
        this->clients_connected.sendMessageToAll(notification);
    } 
}

void Game::_notifyItemChanged(const ConnectionId id, const Response& response, ItemOpcode item_type) {
    Notification* notification;
    Player& player = this->players.at(id);
    switch (item_type) {
        case CLOSE_DOOR_ITM:
        case OPEN_DOOR_ITM:
        case WEAPON_TAKEN_ITM: { 
            notification = new ItemChanged(map_id, item_type, id,
                                (player.getPos().getX())/POINTS_PER_CELL, 
                                (player.getPos().getY())/POINTS_PER_CELL);
            break;
        }
        case MEDICAL_KIT_TAKEN_ITM:
        case FOOD_TAKEN_ITM:
        case BLOOD_TAKEN_ITM: { 
            notification = new ItemChanged(map_id, item_type, id,
                            (player.getPos().getX())/POINTS_PER_CELL, 
                            (player.getPos().getY())/POINTS_PER_CELL,
                            player.getInfo().getLife());
            break;
        }
        case KEY_TAKEN_ITM: { 
            notification = new ItemChanged(map_id, item_type, id,
                            (player.getPos().getX())/POINTS_PER_CELL, 
                            (player.getPos().getY())/POINTS_PER_CELL,
                            player.getInfo().getKey());
            break;
        }
        case TREASURE_TAKEN_ITM: { 
            std::cout<<"TREASURE_TAKEN_ITM: treasure "<< player.getInfo().getTreasure() <<std::endl;
            notification = new ItemChanged(map_id, item_type, id,
                            (player.getPos().getX())/POINTS_PER_CELL, 
                            (player.getPos().getY())/POINTS_PER_CELL,
                            player.getInfo().getTreasure());
            break;
        }
        case BULLETS_TAKEN_ITM: { 
            notification = new ItemChanged(map_id, item_type, id,
                            (player.getPos().getX())/POINTS_PER_CELL, 
                            (player.getPos().getY())/POINTS_PER_CELL,
                            player.getInfo().getNumBullets());
            break;
        }
        default:
            throw Exception("Unknown item type.");
            break;
        }
        this->clients_connected.sendEventToAll(notification);
}

void Game::_move(const ConnectionId id) {
    std::cout <<"Game: player is moving"<< std::endl;
    Player& player = this->players.at(id);
    std::pair<int, int> next_pos = player.getPos().getNextPos(player.getPos().getDirection());
    Response can_move = _canMove(map, player, next_pos);
    std::cout <<"Game: can_move message"<< can_move.message <<std::endl;
    if (can_move.success && ((can_move.message) !=  NO_ITEM_PICKED_UP_MSG)) {
        std::cout <<"Game: player can move and picked up"<< std::endl;
        map.setObjectPos(player.getPos().getX(), player.getPos().getY(), MAP_NONE);
        map.setObjectPos(next_pos.first, next_pos.second, MAP_PLAYER);
        player.updateMovement();
        players_in_map.at(id) = std::make_pair(player.getPos().getX(), player.getPos().getY());
        _notifyMovementEvent(id, Response(true, SUCCESS_MSG));
        _notifyItemChanged(id, can_move, (ItemOpcode)can_move.value);
    } else if (can_move.success) {
        std::cout <<"Game: player can move"<< std::endl;
        map.setObjectPos(player.getPos().getX(), player.getPos().getY(), MAP_NONE);
        map.setObjectPos(next_pos.first, next_pos.second, MAP_PLAYER);
        player.updateMovement();
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

Response Game::_canMove(Map& map, Player& player, std::pair<int, int> next_pos) {
    PlayerPosition pos = player.getPos();
    bool changeCell = _changeCell(pos, next_pos);
    std::cout<<"Game: changed cell is "<<changeCell<<std::endl;
    if (changeCell) {
        std::cout<<"Game: changed cell"<<std::endl;
        int object_code = map.getObjectPos(next_pos.first, next_pos.second);
        std::cout<<"Game: object_code"<<object_code<<std::endl;
        Object* obj = objMap.getObject(object_code);
        if (obj == nullptr) {std::cout<<"Game: object null"<<std::endl;}
        Interact interactor;
        std::cout<<"Game: interactor"<<std::endl;
        Response not_blocking = interactor.interactWith(player, map, obj);
        std::cout<<"Game: cnot_boking"<< not_blocking.success <<std::endl;
        return not_blocking;
    } else { //se mueve dentro de la misma celda
        return Response(true, NO_ITEM_PICKED_UP_MSG);
    }
}

bool Game::_changeCell(PlayerPosition &pos, std::pair<int, int> &next_pos) {
    int current_x = (pos.getX())/POINTS_PER_CELL;
    int current_y = (pos.getY())/POINTS_PER_CELL;
    int next_x = (next_pos.first)/POINTS_PER_CELL;
    int next_y = (next_pos.second)/POINTS_PER_CELL;
    if ((current_x != next_x) || (current_y != next_y)) {
        return true;
    }
    return false;
}

bool Game::_interactWith(Player& player, Map map, Object* obj) {
    return true;
}

void Game::_getPlayerPosition(Id map_id, int init_x, int init_y, Id new_player_id) {
    /*
    std::pair<int, int> inicial_pos;
    if (!positions.empty()){
        inicial_pos = std::make_pair(positions.at(new_player_id).first, positions.at(new_player_id).second);
    } else {
        //obtener una posicion random vacia
    }
    this->respawn_positions[new_player_id] = std::make_pair(inicial_pos.first, inicial_pos.second);
    */
}

void Game::_attack(const ConnectionId id, int iteration) {
    std::cout <<"Game: _attack()"<< std::endl;
    int damage = 0;
    Player& player = this->players.at(id);
    ConnectionId target_id = 0;
    std::cout <<"Game: start _getTargetAttacked"<< std::endl;
    std::pair<ConnectionId, double> result = _getTargetAttacked(id);
    std::cout <<"Game: end _getTargetAttacked"<< std::endl;
    target_id = result.first;
    std::cout <<"Game: target_id"<< target_id <<std::endl;
    std::cout <<"Game: player_id"<< id <<std::endl;
    double distance = result.second;
    std::cout <<"Game: start useWeapon"<< std::endl;
    Response response = player.updateShooting(distance, damage, iteration);
    std::cout <<"Game: num of bullets"<< player.getInfo().getNumBullets()<< std::endl;
    if (id == target_id) {
        std::cout <<"Game: CANT_ATTACK_ITSELF"<< std::endl;
        _notifyEvent(id, Response(false, CANT_ATTACK_ITSELF_ERROR_MSG), ATTACK_EV);
    } else if ((player.getInfo().getNumBullets() == 0) && (player.getInfo().getWeaponTypeEquiped() != KNIFE_TYPE)) {
        std::cout <<"Game: DOESNT HAVE BULLETS"<< std::endl;
        _notifyEvent(id, Response(false, CANT_ATTACK_WITHOUT_BULLETS_ERROR_MSG), ATTACK_EV);
    } else if (target_id == (uint32_t)0) {
        std::cout <<"Game: JUST SHOOTS"<< std::endl;
        //se bajan las balas pero no golpea a nadie
        if (response.success) {
            _reduceBullets(id);
            _notifyEvent(id, Response(true, CANT_ATTACK_UNKNOWN_ID_ERROR_MSG), ATTACK_EV);
        } else {
            _notifyEvent(id, Response(false, CANT_SHOOT_COOLDOWN_ERROR_MSG), ATTACK_EV);
        }
    } else {
        std::cout <<"Game: ATTACKS"<< std::endl;
        Player& target = this->players.at(target_id);
        if((response.success) && (target.getState()->canBeAttacked())) {
            _reduceBullets(id);
            _notifyEvent(id, response, ATTACK_EV); 
            receiveAttack(target_id, damage);
        } else if (response.success) {
            _reduceBullets(id);
            _notifyEvent(id, response, ATTACK_EV); 
        } else {
            _notifyEvent(id, response, ATTACK_EV); 
        }
    }
}

void Game::_reduceBullets(const ConnectionId id) {
    Player& player = this->players.at(id);
    switch(player.getInfo().getWeaponTypeEquiped()) {
        case KNIFE_TYPE: {
            break;
        }
        case CHAIN_CANNON_TYPE:
        case GUN_TYPE: {
            player.reduceBullets(1);
            break;
        }
        case MACHINE_GUN_TYPE: {
            player.reduceBullets(5);
            break;
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

void Game::_deletePlayer(ConnectionId id) {
    std::cout <<"Game: _deletePlayer()"<< std::endl;
    //Player& player = players.at(id);
    this->players_by_name.erase(id);
    std::cout <<"Game: players_by_name erased"<< std::endl;
    this->players_in_map.erase(id);
    std::cout <<"Game: players_in_map erased"<< std::endl;
    _notifyEvent(id, Response(true, SUCCESS_MSG), DELETE_PLAYER_EV);
    std::cout <<"Game: _notifyEvent()"<< std::endl;
    this->players.erase(id);
    std::cout <<"Game: players erased"<< std::endl;
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
    //std::cout <<"Game: adding a new player"<< std::endl;
    this->players.emplace(std::piecewise_construct, 
                std::forward_as_tuple(new_player_id),
                std::forward_as_tuple(100, 100, 2240, 
                                    2240, nickname, new_player_id,
                                    rate));
    //std::cout <<"Game: new player added"<< std::endl;
    map.setObjectPos(100, 100, MAP_PLAYER);
    //de alguna manera me tienen que pasar el nickname
    this->players_by_name[new_player_id] = nickname;
    this->players_in_map.emplace(new_player_id, std::make_pair(100, 100));
    return new_player_id;

}
void Game::notifyNewPlayer(const ConnectionId id) {
    //std::cout <<"Game: new player notified"<< std::endl;
    _notifyEvent(id, Response(true, SUCCESS_MSG), NEW_PLAYER_EV);
    std::unordered_map<ConnectionId, Player>::iterator it;
    for (it = players.begin(); it != players.end(); it++) {
        Player& other = it->second;
        Notification*notification = new Event(YamlMapName, NEW_PLAYER_EV, it->first, other.getPos().getX(), other.getPos().getY(),
                                                other.getPos().getAngle(), other.getInfo().getLife(), other.getInfo().getNumResurrection(),
                                                other.getInfo().getTreasure(), other.getInfo().getNumBullets());
        this->clients_connected.sendEventToOne(id, notification);
    }
}

void Game::deletePlayer(const ConnectionId id) {
    if ((!this->players.count(id)) && (!post_game.isInPostGame(id))) {
        throw Exception("Error in deletePLayer: unknown player id");
    } else if (!post_game.isInPostGame(id)) {
        post_game.add(id, players_by_name.at(id), players.at(id).getInfo().getTreasure());
    } else if(this->players.count(id)) {    
        _deletePlayer(id);
    
    }
}

void Game::updatePlayers(const int iteration) {
    //std::cout <<"Game: enter updatePlayers()"<< std::endl;
    std::unordered_map<ConnectionId, Player>::iterator 
        player_it = this->players.begin();
    while ((!game_ended) && (player_it != this->players.end()) ) {
        ConnectionId id = player_it->first;
        Player& player = player_it->second;
        if (player.isMoving()) {
            _move(id);
        }
        
        if (player.isRotating()) {
            //std::cout <<"Game: player can rotate"<< std::endl;
            player.updateRotation();
            _notifyMovementEvent(id, Response(true, SUCCESS_MSG));
        }

        if (player.isShooting()) {
            std::cout <<"Game: player shoot"<< std::endl;
            _attack(id, iteration);
        } else {
            if (player.machine_gun_cooldown > 0) {
                player.machine_gun_cooldown = std::max((int)(player.chain_cannon_cooldown - iteration *rate),0);
            }
            if (player.chain_cannon_cooldown > 0) {
                player.chain_cannon_cooldown = std::max((int)(player.chain_cannon_cooldown - iteration *rate),0);
            }
            if (!player.gun_can_shoot) {
                player.gun_can_shoot = true;
            }
        }
        if (player.getInfo().getNumResurrection() == MAX_RESURRECTIONS) {
            std::cout <<"Game: player got MAX_RESURRECTIONS "<< std::endl;
            std::string name = players_by_name.at(id);
            std::cout <<"Game: player get name "<< std::endl;
            int treasure = player.getInfo().getTreasure();
            std::cout <<"Game: player get treasure "<< std::endl;
            post_game.add(id, name, treasure);
            std::cout <<"Game: added to post_game "<< std::endl;
            _deletePlayer(id);
        }
        if ((players.size() == 1) && (!post_game.isEmpty())) {
            //END GAME
            game_ended = true;
            std::cout <<"Game: END GAME "<< std::endl;
            std::unordered_map<ConnectionId, Player>::iterator 
            it = this->players.begin();
            std::cout <<"Game: player id "<< (unsigned)it->first<<std::endl;
            std::string name = players_by_name.at(it->first);
            std::cout <<"Game: player get name "<< name <<std::endl;
            int treasure = it->second.getInfo().getTreasure();
            std::cout <<"Game: player get treasure "<< std::endl;
            post_game.add(it->first, name, treasure);
            std::cout <<"Game: added to post_game "<< std::endl;
            _deletePlayer(it->first);
            Notification* notification = post_game.showScores();
            std::cout <<"Game: showed scores "<< std::endl;
            this->clients_connected.sendEventToAll(notification);
            break;
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

void Game::changeWeapon(const ConnectionId id, int& weapon) {
    std::cout <<"Game:change_weapon"<< std::endl;
    Player& player = this->players.at(id);
    if (!player.getInfo().hasWeapon(weapon)) {
        std::cout <<"Game: not in inventory"<< std::endl;
        _notifyChangeWeaponEvent(id, Response(false, NO_WEAPON_IN_INVENTORY_ERROR_MSG), weapon);
    } else {
        std::cout <<"Game: in inventory"<< std::endl;
        player.changeWeapon(weapon);
        std::cout <<"Game: changed weapon"<< std::endl;
        _notifyChangeWeaponEvent(id, Response(true, SUCCESS_MSG), weapon);
    }
}

void Game::receiveAttack(const ConnectionId id, int& damage) {
    Player& player = this->players.at(id);
    Response response = player.receiveAttack(damage);
    if (response.message == PLAYER_DIED_MSG) {
        std::cout<<"Game: PLAYER_DIED_MSG"<<std::endl;
        _notifyEvent(id, response, DEATH_EV);
        //POSICION EN EL MAPA: CAMBIAR SEGUN LO QUE ESTE EN respawn_positions!!!!!!
        player.setPosition(100, 100);
        std::cout<<"Game: POS X: "<< player.getPos().getX() <<std::endl;
        std::cout<<"Game: POS Y: "<< player.getPos().getY() <<std::endl;
        players_in_map[id] = std::make_pair(player.getPos().getX(), player.getPos().getY());
        _notifyEvent(id, player.resurrect(), RESURRECT_EV);
    } else {
        std::cout<<"Game: BE_ATTACKED_EV"<<std::endl;
        _notifyEvent(id, response, BE_ATTACKED_EV);
    }
}
