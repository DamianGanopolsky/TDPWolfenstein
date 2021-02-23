#include "game.h"
#include "./../clients_connected.h"

#define MAX_NUM 999999999
#define PATH_TO_MAP "../Maps/"
#define YAML_EXT ".yaml"
#define FOV 45
#include <cstdlib>

Game::Game(ClientsConnected& clients_connected, std::string map_Yaml, int& rate) : 
                            map_Yaml(map_Yaml),
                            path_Yaml(PATH_TO_MAP+map_Yaml+YAML_EXT),
                            players(), players_by_name(),
                            players_in_map(), respawn_positions(),
                            clients_connected(clients_connected),
                            post_game(map_Yaml), map_id(2), 
                            map(path_Yaml),
                            game_ended(false), objMap(), rate(rate) 
                            {
                                YAML::Node config = YAML::LoadFile(PATH_TO_MAP+map_Yaml+YAML_EXT);
                                this->height = (config["Map"]["map_dimentions"]["height"].as<int>())*GameConfig.points_per_cell;
                                this->width = (config["Map"]["map_dimentions"]["width"].as<int>())*GameConfig.points_per_cell;
                            }

Game::~Game() {}

void Game::_notifyMovementEvent(const ConnectionId id, const Response& response) {
    Notification* notification;
    Player& player = this->players.at(id);
    if (response.success) {
        notification = new Event(map_Yaml, MOVEMENT_EV, id, player.getPos().getX(),
                                 player.getPos().getY(), player.getPos().getAngle(),
                                 player.isMoving(), player.isShooting());
        this->clients_connected.sendEventToAll(notification);
    } else {
        notification = new Message(ERROR_MSSG, response.message);
        this->clients_connected.sendMessageToAll(notification);
    } 
}

void Game::_notifyChangeWeaponEvent(const ConnectionId id, const Response& response, int weapon) {
    Notification* notification;
    if (response.success) {
        notification = new Event(map_Yaml, CHANGE_WEAPON_EV, id, weapon);
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
                notification = new Event(map_Yaml, event_type, id, player.getPos().getX(), player.getPos().getY(),
                                            player.getPos().getAngle(), player.getInfo().getLife(), player.getInfo().getNumResurrection(),
                                            player.getInfo().getTreasure(), player.getInfo().getNumBullets());
                break;
            }
            case ATTACK_EV: {
                notification = new Event(map_Yaml, event_type, id,
                                        player.getInfo().getNumBullets());
                break;
            }
            case BE_ATTACKED_EV: {
                notification = new Event(map_Yaml, event_type, id, player.getInfo().getLife());
                break;
            }
            case DEATH_EV: {
                notification = new Event(map_Yaml, event_type, id, player.getPos().getX(), player.getPos().getY());
                break;
            }
            //case DELETE_PLAYER_EV:
            case CHANGE_WEAPON_EV:
            case MOVEMENT_EV:
            case SCORES_EV:
            case START_EV: {
                break;
            }

        }
        this->clients_connected.sendEventToAll(notification);
    }
}

void Game::_notifyItemChanged(const ConnectionId id, ItemOpcode item_type) {
    Notification* notification;
    Player& player = this->players.at(id);
    switch (item_type) {
        case CLOSE_DOOR_ITM:
        case OPEN_DOOR_ITM:
        case WEAPON_TAKEN_ITM: { 
            notification = new ItemChanged(map_id, item_type, id,
                                (player.getPos().getX())/GameConfig.points_per_cell, 
                                (player.getPos().getY())/GameConfig.points_per_cell);
            break;
        }
        case MEDICAL_KIT_TAKEN_ITM:
        case FOOD_TAKEN_ITM:
        case BLOOD_TAKEN_ITM: { 
            notification = new ItemChanged(map_id, item_type, id,
                            (player.getPos().getX())/GameConfig.points_per_cell, 
                            (player.getPos().getY())/GameConfig.points_per_cell,
                            player.getInfo().getLife());
            break;
        }
        case KEY_TAKEN_ITM: { 
            notification = new ItemChanged(map_id, item_type, id,
                            (player.getPos().getX())/GameConfig.points_per_cell, 
                            (player.getPos().getY())/GameConfig.points_per_cell,
                            player.getInfo().getKey());
            break;
        }
        case TREASURE_TAKEN_ITM: {
            notification = new ItemChanged(map_id, item_type, id,
                            (player.getPos().getX())/GameConfig.points_per_cell, 
                            (player.getPos().getY())/GameConfig.points_per_cell,
                            player.getInfo().getTreasure());
            break;
        }
        case BULLETS_TAKEN_ITM: { 
            notification = new ItemChanged(map_id, item_type, id,
                            (player.getPos().getX())/GameConfig.points_per_cell, 
                            (player.getPos().getY())/GameConfig.points_per_cell,
                            player.getInfo().getNumBullets());
            break;
        }
        case BULLETS_DROPPED_ITM:
        case MACHINE_GUN_DROPPED_ITM:
        case CHAIN_CANNON_DROPPED_ITM: {
            break;
        }
        default:
            throw Exception("Unknown item type.");
            break;
        }
        this->clients_connected.sendEventToAll(notification);
}

void Game::_notifyItemDropped(const ConnectionId id, ItemOpcode item_type, int x, int y) {
    Notification* notification;
    switch (item_type) {
        case CLOSE_DOOR_ITM:
        case OPEN_DOOR_ITM:
        case WEAPON_TAKEN_ITM:
        case MEDICAL_KIT_TAKEN_ITM:
        case FOOD_TAKEN_ITM:
        case BLOOD_TAKEN_ITM:
        case KEY_TAKEN_ITM:
        case TREASURE_TAKEN_ITM:
        case BULLETS_TAKEN_ITM: {
            break;
        }
        case BULLETS_DROPPED_ITM:
        case MACHINE_GUN_DROPPED_ITM:
        case CHAIN_CANNON_DROPPED_ITM: {
            notification = new ItemChanged(map_id, item_type, id,
                                            x/GameConfig.points_per_cell, 
                                            y/GameConfig.points_per_cell);
            break;
        }
        default:
            throw Exception("Unknown item type.");
            break;
        }
        this->clients_connected.sendEventToAll(notification);
}

void Game::_dropItems(ConnectionId id, int x, int y) {
    Player& player = this->players.at(id);
    int weapon = player.getInfo().getWeaponTypeEquiped();
    switch (weapon) {
        case MACHINE_GUN_TYPE: {
            std::pair <int, int> pos = _getNearestCellEmpty(x, y);
            map.setObjectPos(pos.first, pos.second, MAP_MACHINE_GUN);
            _notifyItemDropped(id, MACHINE_GUN_DROPPED_ITM,
                                pos.first, pos.second);
            break;
        }
        case CHAIN_CANNON_TYPE: {
            std::pair <int, int> pos = _getNearestCellEmpty(x, y);
            map.setObjectPos(pos.first, pos.second, MAP_CHAIN_CANNON);
            _notifyItemDropped(id, CHAIN_CANNON_DROPPED_ITM,
                                pos.first, pos.second);
            break;
        }
        case GUN_TYPE:
        case KNIFE_TYPE: {
            break;
        }
    }
    std::pair <int, int> pos_bullets = _getNearestCellEmpty(x, y);
    map.setObjectPos(pos_bullets.first, pos_bullets.second, MAP_BULLET);
    _notifyItemDropped(id, BULLETS_DROPPED_ITM, 
                        pos_bullets.first, pos_bullets.second);
}

std::pair<int, int> Game::_getNearestCellEmpty(int pos_x, int pos_y) {
    std::pair<int, int> pos;
    for (int i = 1; i != 35; i++) {
        pos = map.getNextPos(UP_DIR, pos_x, pos_y, i);
        if(map.getObjectPos((pos.first*GameConfig.points_per_cell),
        (pos.second*GameConfig.points_per_cell)) == MAP_NONE) {
            return std::make_pair((pos.first*GameConfig.points_per_cell),
            (pos.second*GameConfig.points_per_cell));
        }
        pos = map.getNextPos(DOWN_DIR, pos_x, pos_y, i);
        if(map.getObjectPos((pos.first*GameConfig.points_per_cell),
        (pos.second*GameConfig.points_per_cell)) == MAP_NONE) {
            return std::make_pair((pos.first*GameConfig.points_per_cell),
            (pos.second*GameConfig.points_per_cell));
        }
        pos = map.getNextPos(LEFT_DIR, pos_x, pos_y, i);
        if(map.getObjectPos((pos.first*GameConfig.points_per_cell),
        (pos.second*GameConfig.points_per_cell)) == MAP_NONE) {
            return std::make_pair((pos.first*GameConfig.points_per_cell),
            (pos.second*GameConfig.points_per_cell));
        }
        pos = map.getNextPos(RIGHT_DIR, pos_x, pos_y, i);
        if(map.getObjectPos((pos.first*GameConfig.points_per_cell),
        (pos.second*GameConfig.points_per_cell)) == MAP_NONE) {
            return std::make_pair((pos.first*GameConfig.points_per_cell),
            (pos.second*GameConfig.points_per_cell));
        }
    }
    return std::make_pair(1,1);
}
void Game::_move(const ConnectionId id) {
    Player& player = this->players.at(id);
    std::pair<int, int> next_pos = player.getPos().getNextPos(player.getPos().getDirection());
    Response can_move = _canMove(map, player, next_pos);
    if (can_move.success && ((can_move.message) !=  NO_ITEM_PICKED_UP_MSG)) {
        map.setObjectPos(player.getPos().getX(), player.getPos().getY(), MAP_NONE);
        map.setObjectPos(next_pos.first, next_pos.second, MAP_PLAYER);
        player.updateMovement();
        players_in_map.at(id) = std::make_pair(player.getPos().getX(), player.getPos().getY());
        _notifyMovementEvent(id, Response(true, SUCCESS_MSG));
        _notifyItemChanged(id, (ItemOpcode)can_move.value);
    } else if (can_move.success) {
        map.setObjectPos(player.getPos().getX(), player.getPos().getY(), MAP_NONE);
        map.setObjectPos(next_pos.first, next_pos.second, MAP_PLAYER);
        player.updateMovement();
        players_in_map.at(id) = std::make_pair(player.getPos().getX(), player.getPos().getY());
        _notifyMovementEvent(id, Response(true, SUCCESS_MSG));
    } else {
        player.stopMoving();
        _notifyMovementEvent(id, Response(false, CANT_MOVE_ERROR_MSG));
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
}

bool Game::_changeCell(PlayerPosition &pos, std::pair<int, int> &next_pos) {
    int current_x = (pos.getX())/GameConfig.points_per_cell;
    int current_y = (pos.getY())/GameConfig.points_per_cell;
    int next_x = (next_pos.first)/GameConfig.points_per_cell;
    int next_y = (next_pos.second)/GameConfig.points_per_cell;
    if ((current_x != next_x) || (current_y != next_y)) {
        return true;
    }
    return false;
}

bool Game::_interactWith(Player& player, Map map, Object* obj) {
    return true;
}

void Game::_getPlayerPosition(ConnectionId new_player_id) {
    YamlParser yamlparser(path_Yaml);
    std::map <int,std::pair<int,int>> positions = yamlparser.load_players(path_Yaml);
    std::pair<int, int> inicial_pos;
    if (!positions.empty()){
        inicial_pos = std::make_pair(positions.at(new_player_id).first, positions.at(new_player_id).second);
        positions.erase(new_player_id);
    } else {
        throw Exception("Not enough positions established in the map for the amount of players.");
    }
    this->respawn_positions[new_player_id] = std::make_pair(inicial_pos.first, inicial_pos.second);
}

void Game::_attack(const ConnectionId id, int iteration) {
    int damage = 0;
    Player& player = this->players.at(id);
    ConnectionId target_id = 0;
    std::pair<ConnectionId, double> result = _getTargetAttacked(id);
    target_id = result.first;
    double distance = result.second;
    Response response = player.updateShooting(distance, damage, iteration);
    if (id == target_id) {
        _notifyEvent(id, Response(false, CANT_ATTACK_ITSELF_ERROR_MSG), ATTACK_EV);
    } else if ((player.getInfo().getNumBullets() == 0) && (player.getInfo().getWeaponTypeEquiped() != KNIFE_TYPE)) {
        _notifyEvent(id, Response(false, CANT_ATTACK_WITHOUT_BULLETS_ERROR_MSG), ATTACK_EV);
    } else if (target_id == (uint32_t)0) {
        //se bajan las balas pero no golpea a nadie
        if (response.success) {
            _reduceBullets(id);
            _notifyEvent(id, Response(true, CANT_ATTACK_UNKNOWN_ID_ERROR_MSG), ATTACK_EV);
        } else {
            _notifyEvent(id, Response(false, CANT_SHOOT_COOLDOWN_ERROR_MSG), ATTACK_EV);
        }
    } else {
        Player& target = this->players.at(target_id);
        if((response.success) && (target.getState()->canBeAttacked())) {
            _reduceBullets(id);
            _notifyEvent(id, response, ATTACK_EV); 
            bool is_dead = receiveAttack(target_id, damage);
            if (is_dead) {
                player.addKill();
            }
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
    std::unordered_map<ConnectionId, std::pair<int, int>>::iterator it;
    std::pair<ConnectionId, double>closer_player =  std::make_pair(0, MAX_NUM);
    for (it = players_in_map.begin(); it != players_in_map.end(); it++) {
        if (it->first != attacker_id) {
            int attacker_x = players_in_map.at(attacker_id).first;
            int attacker_y = players_in_map.at(attacker_id).second;
            float attacker_angle =(players.at(attacker_id).getPos().getAngle());
            int other_player_x=it->second.first;
            int other_player_y=it->second.second;
            int x_delta = (players_in_map.at(attacker_id).first - it->second.first);
            int y_delta = (players_in_map.at(attacker_id).second - it->second.second);
            double distance = sqrt( pow(x_delta, 2) + pow(y_delta, 2) ); 
            if((is_player_target(attacker_x, attacker_y, attacker_angle, \
            other_player_x,other_player_y))&&(distance<900)){
                closer_player.first=it->first;
                closer_player.second=distance;
            }
        }
    }
    return closer_player;
}

bool Game::is_player_target(int pos_x_attacker, int pos_y_attacker, float vision_angle_attacker, \
int pos_x_other_player,int pos_y_other_player){
	float x = pos_x_attacker - pos_x_other_player;
	float y = pos_y_attacker - pos_y_other_player;
    float angle=atan2(y,x);
    angle=angle * 180/GameConfig.pi;
    angle=180-angle;
    int diff=std::abs(angle-vision_angle_attacker);
    if(diff<10){
        return true;
    }
    else{
        return false;
    }
}

void Game::_deletePlayer(ConnectionId id) {
    this->players_by_name.erase(id);
    this->players_in_map.erase(id);
    this->players.erase(id);
}

void Game::newPlayer(const ConnectionId id, std::string& nickname) {
    _getPlayerPosition(id);
    this->players.emplace(std::piecewise_construct, 
                std::forward_as_tuple(id),
                std::forward_as_tuple(
                    respawn_positions.at(id).first, 
                    respawn_positions.at(id).second,
                    this->width, this->height,
                    nickname, id,
                    rate));
    map.setObjectPos(respawn_positions.at(id).first,
                    respawn_positions.at(id).second, 
                    MAP_PLAYER);
    this->players_by_name[id] = nickname;
    this->players_in_map.emplace(id, 
                    std::make_pair(
                    respawn_positions.at(id).first, 
                    respawn_positions.at(id).second));
}

void Game::notifyNewPlayer(const ConnectionId id) {
    _notifyEvent(id, Response(true, SUCCESS_MSG), NEW_PLAYER_EV);
    std::unordered_map<ConnectionId, Player>::iterator it;
    for (it = players.begin(); it != players.end(); it++) {
        Player& other = it->second;
        Notification*notification = new Event(map_Yaml, NEW_PLAYER_EV, it->first, other.getPos().getX(), other.getPos().getY(),
                                                other.getPos().getAngle(), other.getInfo().getLife(), other.getInfo().getNumResurrection(),
                                                other.getInfo().getTreasure(), other.getInfo().getNumBullets());
        this->clients_connected.sendEventToOne(id, notification);
    }
}

void Game::deletePlayer(const ConnectionId id) {
    if ((!this->players.count(id)) && (!post_game.isInPostGame(id))) {
        throw Exception("Error in deletePLayer: unknown player id");
    }
    if (!post_game.isInPostGame(id)) {
        post_game.add(id, players_by_name.at(id), 
                    players.at(id).getInfo().getTreasure(), 
                    players.at(id).getInfo().getKills());
    } 
    if(this->players.count(id)) {
        _deletePlayer(id);
    
    }
}

bool Game::updatePlayers(int& iteration) {
    std::unordered_map<ConnectionId, Player>::iterator 
        player_it = this->players.begin();
    while ((!game_ended) && (player_it != this->players.end()) ) {
        ConnectionId id = player_it->first;
        Player& player = player_it->second;
        if (player.isMoving()) {
            _move(id);
        }
        
        if (player.isRotating()) {
            player.updateRotation();
            _notifyMovementEvent(id, Response(true, SUCCESS_MSG));
        }

        if (player.isShooting()) {
            _attack(id, iteration);
        } else if (!player.gun_can_shoot) {
            player.gun_can_shoot = true;
        }
        if (player.machine_gun_cooldown > 0) {
            player.machine_gun_cooldown = std::max((int)(player.machine_gun_cooldown - iteration),0);
        }
        if (player.chain_cannon_cooldown > 0) {
            player.chain_cannon_cooldown = std::max((int)(player.chain_cannon_cooldown - iteration),0);
        }
        if (player.isAlive()) {
            Response response = player.updateLife(iteration);
            _notifyEvent(id, response, BE_ATTACKED_EV);
        }
        if (player.life_cooldown > 0) {
            player.life_cooldown = std::max((int)(player.life_cooldown - iteration),0);
        }
        if ((player.getInfo().getNumBullets() == 0) && (!player.forced_weapon)) {
            int weapon = player.getInfo().getWeaponTypeEquiped();
            changeWeapon(id, KNIFE_TYPE);
            player.forced_weapon = true;
            player.weapon_equiped_before = weapon;
        }
        if ((player.getInfo().getNumBullets() != 0) && (player.forced_weapon)) {
            changeWeapon(id, player.weapon_equiped_before);
            player.forced_weapon = false;
        }
        if (player.getInfo().getNumResurrection() == GameConfig.max_resurrections) {
            std::string name = players_by_name.at(id);
            int treasure = player.getInfo().getTreasure();
            post_game.add(id, name, treasure, player.getInfo().getKills());
            _deletePlayer(id);
        }
        if ((players.size() == 1) && (!post_game.isEmpty())) {
            //END GAME
            game_ended = true;
            std::unordered_map<ConnectionId, Player>::iterator 
            it = this->players.begin();
            std::string name = players_by_name.at(it->first);
            int treasure = it->second.getInfo().getTreasure();
            post_game.add(it->first, name, treasure, it->second.getInfo().getKills());
            _deletePlayer(it->first);
            Notification* notification = post_game.showScores();
            this->clients_connected.sendEventToAll(notification);
            return false;
        }

        ++player_it;
    }
    return true;
}

void Game::updateOpenDoorsLifetime(const int iteration) {}

void Game::startMovingUp(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.startMovingUp();
}

void Game::startMovingDown(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.startMovingDown();
}

void Game::startMovingLeft(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.startMovingLeft();
}

void Game::startMovingRight(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.startMovingRight();
}

void Game::stopMoving(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.stopMoving();
}

void Game::startRotatingLeft(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.startRotatingLeft();
}

void Game::startRotatingRight(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.startRotatingRight();
}

void Game::stopRotating(const ConnectionId id) {
    Player& player = this->players.at(id);
    player.stopRotating();
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
    /*Player& player = this->players.at(id);
    PlayerPosition pos = player.getPos();

    int object_code = map[pos.getX()][pos.getY()];
    Object obj = objMap.getObject(object_code);
    bool door_opened = _interactWith(player, map, obj);
    if (!door_opened) {
        _notifyItemChanged(id, Response(false, NO_KEY_TO_OPEN_CLOSED_DOOR), OPEN_DOOR_ITM);
    } else {
        _notifyItemChanged(id, Response(true, SUCCESS_MSG), OPEN_DOOR_ITM);
    }*/
}

void Game::changeWeapon(const ConnectionId id, const int& weapon) {
    Player& player = this->players.at(id);
    if (!player.getInfo().hasWeapon(weapon)) {
        _notifyChangeWeaponEvent(id, Response(false, NO_WEAPON_IN_INVENTORY_ERROR_MSG), weapon);
    } else {
        player.changeWeapon(weapon);
        _notifyChangeWeaponEvent(id, Response(true, SUCCESS_MSG), weapon);
    }
}

bool Game::receiveAttack(const ConnectionId id, int& damage) {
    Player& player = this->players.at(id);
    Response response = player.receiveAttack(damage);
    if (response.message == PLAYER_DIED_MSG) {
        _dropItems(id, player.getPos().getX(), player.getPos().getY());
        map.setObjectPos(player.getPos().getX(), player.getPos().getY(), MAP_NONE);
        _notifyEvent(id, response, DEATH_EV);
        player.setPosition(respawn_positions.at(id).first,
                            respawn_positions.at(id).second);
        players_in_map[id] = std::make_pair(player.getPos().getX(), player.getPos().getY());
        Response response_resurrect = player.resurrect();
        _notifyEvent(id, response_resurrect, RESURRECT_EV);
        if (response_resurrect.success) {
            _notifyChangeWeaponEvent(id, response_resurrect, KNIFE_TYPE);
        }
        return true;
    }
    _notifyEvent(id, response, BE_ATTACKED_EV);
    return false;
}
