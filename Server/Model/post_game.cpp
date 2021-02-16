#include "./post_game.h"

PostGame::PostGame(std::string map_name) : 
                    map_name(map_name), is_empty(true),
                    losers(), scores(), names() {}

PostGame::~PostGame() {}

void PostGame::_getBestScores() {
    std::unordered_map<ConnectionId, std::pair<std::string, int>>::iterator it;
    std::string name;
    ConnectionId id;
    int score = losers.begin()->second.second;
    for (int i = 0; i == 5; i++) {
        for (it = losers.begin(); it != losers.end(); it++) {
            if (score < it->second.second) {
                name = it->second.first;
                score = it->second.second;
                id = it->first;
            }
        }
        this->scores[i] = score;
        this->names[i] = name;
        losers.erase(id);
    }

}

void PostGame::add(ConnectionId id, std::string nickname, int score) {
    if (losers.count(id) > 0) {
        throw Exception("Repeated client_id in PostGame.");
    }
    this->losers[id] = std::make_pair(nickname, score);
    this->is_empty = false;
}

Notification* PostGame::showScores() {
    Notification* notification;
    _getBestScores();
    std::string empty;
    empty = " ";
    switch (losers.size()){
        case 0:
        case 1: {
            throw Exception ("No players to show scores.");
        }
        case 2: {
            notification = new Event(map_name, SCORES_EV, 2, names[0], 
                                        scores[0], names[1],
                                        scores[1], empty, 0, empty, 
                                        0, empty, 0);
            break;
        }
        case 3: {
            notification = new Event(map_name, SCORES_EV, 3, names[0],
                                        scores[0], names[1], scores[1], 
                                        names[2], scores[2], empty, 0,
                                        empty, 0);
            break;
        }
        case 4: {
            notification = new Event(map_name, SCORES_EV, 4, names[0],
                                        scores[0], names[1], scores[1], 
                                        names[2], scores[2], names[3],
                                        scores[3], empty, 0);
            break;
        }
        default: {
            notification = new Event(map_name, SCORES_EV, 5, names[0],
                                        scores[0], names[1], scores[1], 
                                        names[2], scores[2], names[3],
                                        scores[3], names[4], scores[4]);
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