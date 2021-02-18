#ifndef PRE_GAME_H
#define PRE_GAME_H

#include "./game.h"

class PreGame {
    ConnectionId new_connection_id;
    bool first_iteration;
    int max_players;
    std::list<ConnectionId> players;

    public:
        PreGame(ClientsConnected& clients_connected, std::string map_Yaml, int& rate);
        ~PreGame();
        Game game;
        int update(int iterations);
        ConnectionId addPlayer();
        void deletePlayer(const ConnectionId id);
};

#endif