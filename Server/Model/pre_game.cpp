#include "./pre_game.h"

PreGame::PreGame(ClientsConnected& clients_connected, std::string map_Yaml, int& rate) :  
                    new_connection_id(1),
                    players(0), game(clients_connected, map_Yaml, rate) {
                        this->max_players = 2;
                    }

PreGame::~PreGame() {}

bool PreGame::update(int iteration) {
    if (players == max_players){
        game.updatePlayers(iteration);
        return true;
    }
    return false;
}

ConnectionId PreGame::addPlayer() {
    if (players != max_players) {
        ConnectionId id = this->new_connection_id;
        this->game.newPlayer(id);
        ++(this->new_connection_id);
        ++(this->players);
        return id;
    }
    return 0;
    //MANDAR MENSAJE PARTIDA LLENA
}

void PreGame::notifyNewPlayer(const ConnectionId id) {
    this->game.notifyNewPlayer(id);
    
}

void PreGame::deletePlayer(const ConnectionId id) {
    if (players == max_players) {
        game.deletePlayer(id);
    }
}