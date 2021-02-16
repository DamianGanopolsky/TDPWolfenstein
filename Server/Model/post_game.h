#ifndef POST_GAME_H
#define POST_GAME_H

#include <unordered_map>
#include <string>
#include "../Notifications/notification.h"
#include "../Notifications/event.h"
#include "../../Common/defs.h"

class PostGame {
    std::string map_name;
    bool is_empty;
    std::unordered_map<ConnectionId, std::pair<std::string, int>> losers;
    int scores[5];
    std::string names[5];
    void _getBestScores();
    
    public:
        PostGame(std::string map_name);
        ~PostGame();
        void add(ConnectionId id, std::string nickname, int score);
        Notification* showScores();
        bool isInPostGame(ConnectionId id);
        bool isEmpty();
        void erase(ConnectionId id);
};


#endif