#include "./post_game.h"

PostGame::PostGame(std::string map_name) : 
                    map_name(map_name), is_empty(true),
                    losers(), scores(), names() {
                       std::cout<<"PostGame: start()"<<std::endl; 
                    }

PostGame::~PostGame() {}

void PostGame::_copyOfMap() {
    std::unordered_map<ConnectionId, std::pair<std::string, int>>::iterator it;
    for (it = losers.begin(); it != losers.end(); it++) {
        this->losers_copy.emplace(
        std::piecewise_construct, std::forward_as_tuple(it->first),
        std::forward_as_tuple(std::make_pair(it->second.first, it->second.second)));
    }
}

void PostGame::_getBestScores() {
    std::cout<<"PostGame: _getBestScores()"<<std::endl;
    _copyOfMap();
    std::unordered_map<ConnectionId, std::pair<std::string, int>>::iterator it;
    std::string name;
    ConnectionId id;
    std::cout<<"PostGame: start"<<std::endl;
    for (int i = 0; i <= (num_players-1); i++) {
        std::cout<<"PostGame: enter in for"<<std::endl;
        int score = -1;
        for (it = losers_copy.begin(); it != losers_copy.end(); it++) {
            std::cout<<"PostGame: enter in for2"<<std::endl;
            if (score < it->second.second) {
                std::cout<<"PostGame:enters in if"<<std::endl;
                name = it->second.first;
                std::cout<<"PostGame: names_ "<<name<<std::endl;
                score = it->second.second;
                std::cout<<"PostGame: score_ "<<score<<std::endl;
                id = it->first;
                std::cout<<"PostGame: id_ "<<id<<std::endl;
            }
        }
        std::cout<<"PostGame: names "<<name<<std::endl;
        std::cout<<"PostGame: score "<<score<<std::endl;
        std::cout<<"PostGame: id "<<id<<std::endl;
        this->scores[i] = score;
        this->names[i] = name;
        losers_copy.erase(id);
    }
    std::cout<<"PostGame: end _getBestScores()"<<std::endl;
}

void PostGame::add(ConnectionId id, std::string nickname, int score) {
    std::cout<<"PostGame: add"<< (unsigned)id <<std::endl;
    std::cout<<"PostGame: nickname"<< nickname <<std::endl;
    std::cout<<"PostGame: score"<< score <<std::endl;
    if (losers.count(id) > 0) {
        throw Exception("Repeated client_id in PostGame.");
    }
    losers.emplace(
        std::piecewise_construct, std::forward_as_tuple(id),
        std::forward_as_tuple(std::make_pair(nickname, score)));
    //this->losers[id] = std::make_pair(nickname, score);
    this->is_empty = false;
}

Notification* PostGame::showScores() {
    std::cout<<"PostGame: showScores()"<<std::endl;
    std::cout<<"PostGame: name 1"<<names[0]<<std::endl;
    std::cout<<"PostGame: name 2"<<names[1]<<std::endl;
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