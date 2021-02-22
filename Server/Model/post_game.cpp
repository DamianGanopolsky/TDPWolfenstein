#include "./post_game.h"

PostGame::PostGame(std::string map_name) : 
                    map_name(map_name), is_empty(true),
                    losers(), treasures(), kills(),
                    scores(), names() {
                    }

PostGame::~PostGame() {}

void PostGame::_copyOfMap() {
    std::unordered_map<ConnectionId, std::pair<std::string, std::vector<int>>>::iterator it;
    for (it = losers.begin(); it != losers.end(); it++) {
        std::string nickname = it->second.first;
        int treasure = it->second.second[0];
        int kills = it->second.second[1];
        int values[] = {treasure, kills};
        std::vector<int> vector (values, values + sizeof(values) / sizeof(int));
        this->losers_copy.emplace(
        std::piecewise_construct, std::forward_as_tuple(it->first),
        std::forward_as_tuple(std::make_pair(nickname, vector)));
    }
}

void PostGame::_getBestScores() {
    _copyOfMap();
    std::unordered_map<ConnectionId, std::pair<std::string, std::vector<int>>>::iterator it;
    std::string name;
    int kills;
    int treasure;
    ConnectionId id;
    for (int i = 0; i <= (num_players-1); i++) {
        int score = -1;
        for (it = losers_copy.begin(); it != losers_copy.end(); it++) {
            int value = ((it->second.second[0]*GameConfig.treasure_weight_final_score)+
                (it->second.second[1]*GameConfig.kills_weight_final_score));
            if (score < value) {
                name = it->second.first;
                treasure = it->second.second[0];
                kills = it->second.second[1];
                id = it->first;
                score = value;
            }
        }
        this->names[i] = name;
        this->treasures[i] = treasure;
        this->kills[i] = kills;
        this->scores[i] = score;
        losers_copy.erase(id);
    }
}

void PostGame::add(ConnectionId id, std::string nickname, int treasure, int kills) {
    int values[] = {treasure, kills};
    std::vector<int> vector (values, values + sizeof(values) / sizeof(int));
    if (losers.count(id) > 0) {
        throw Exception("Repeated client_id in PostGame.");
    }
    losers.emplace(
        std::piecewise_construct, std::forward_as_tuple(id),
        std::forward_as_tuple(std::make_pair(nickname, vector)));
    //this->losers[id] = std::make_pair(nickname, score);
    this->is_empty = false;
}

Notification* PostGame::showScores() {
    Notification* notification;
    this->num_players = (int)losers.size();
    _getBestScores();
    std::string empty;
    empty = " ";
    switch (num_players){
        case 0:
        case 1: {
            throw Exception ("No players to show scores.");
        }
        case 2: {
            notification = new Event(map_name, SCORES_EV, 2, names[0], 
                                        treasures[0], kills[0], 
                                        scores[0], names[1],
                                        treasures[1], kills[1], 
                                        scores[1], empty, 0, 0, 0,
                                        empty, 0, 0, 0,
                                        empty, 0, 0, 0);
            break;
        }
        case 3: {
            notification = new Event(map_name, SCORES_EV, 3, names[0], 
                                        treasures[0], kills[0], 
                                        scores[0], names[1],
                                        treasures[1], kills[1], 
                                        scores[1], names[2], 
                                        treasures[2], kills[2], 
                                        scores[2], empty, 0, 0, 0,
                                        empty, 0, 0, 0);
            break;
        }
        case 4: {
            notification = new Event(map_name, SCORES_EV, 4, names[0], 
                                        treasures[0], kills[0], 
                                        scores[0], names[1],
                                        treasures[1], kills[1], 
                                        scores[1], names[2], 
                                        treasures[2], kills[2], 
                                        scores[2], names[3],
                                        treasures[3], kills[3], 
                                        scores[3], empty, 0, 0, 0);
            break;
        }
        default: {
            notification = new Event(map_name, SCORES_EV, 5, names[0], 
                                        treasures[0], kills[0], 
                                        scores[0], names[1],
                                        treasures[1], kills[1], 
                                        scores[1], names[2], 
                                        treasures[2], kills[2], 
                                        scores[2], names[3],
                                        treasures[3], kills[3], 
                                        scores[3], names[4], 
                                        treasures[4], kills[4],
                                        scores[4]);
            break;
        }
    }
    return notification;
}

bool PostGame::isInPostGame(ConnectionId id) {
    if (losers.count(id) == 0) {
        return false;
    }
    return true;
}

bool PostGame::isEmpty() {
    return this->is_empty;
}

void PostGame::erase(ConnectionId id) {
    if (losers.count(id) == 0) {
        throw Exception("Invalid client_id in PostGame.");
    }
    this->losers.erase(id);
}