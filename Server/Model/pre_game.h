#ifndef PRE_GAME_H
#define PRE_GAME_H

#include "./game.h"

class PreGame {
    ConnectionId new_connection_id;
    int max_players;
    int players;

    public:
        PreGame(ClientsConnected& clients_connected, std::string map_Yaml, int& rate);
        ~PreGame();
        Game game;
        bool update(int iterations);
        ConnectionId addPlayer();
        void notifyNewPlayer(const ConnectionId id);
        void deletePlayer(const ConnectionId id);
};

#endif