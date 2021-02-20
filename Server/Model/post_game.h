#ifndef POST_GAME_H
#define POST_GAME_H

#include <unordered_map>
#include <string>
#include "../Notifications/notification.h"
#include "../Notifications/event.h"
#include "../../Common/defs.h"
#include "./constants/config_player.h"

class PostGame {
    std::string map_name;
    bool is_empty;
    std::unordered_map<ConnectionId, std::pair<std::string, std::vector<int>>> losers;
    std::unordered_map<ConnectionId, std::pair<std::string, std::vector<int>>> losers_copy;
    int treasures[5];
    int kills[5];
    int scores[5];
    std::string names[5];
    int num_players;
    void _getBestScores();
    void _copyOfMap();
    
    public:
        PostGame(std::string map_name);
        ~PostGame();
        void add(ConnectionId id, std::string nickname, int treasure, int kills);
        Notification* showScores();
        bool isInPostGame(ConnectionId id);
        bool isEmpty();
        void erase(ConnectionId id);
};


#endif