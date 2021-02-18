#include "./pre_game.h"

PreGame::PreGame(ClientsConnected& clients_connected, std::string map_Yaml, int& rate) :  
                    new_connection_id(1), first_iteration(false),
                    players(), game(clients_connected, map_Yaml, rate) {
                        this->max_players = 2;
                    }

PreGame::~PreGame() {}

int PreGame::update(int iteration) {
    if (((int)players.size() == max_players) && (first_iteration)) {
        std::list<ConnectionId>::iterator it;
        for(it = players.begin(); it != players.end(); ++it) {
            this->game.newPlayer(*it);
            this->game.notifyNewPlayer(*it);
        }
        game.updatePlayers(iteration);
        return -1;
    } else if ((int)players.size() == max_players){
        game.updatePlayers(iteration);
        return -1;
    }
    return ((int)players.size() - max_players);
}

ConnectionId PreGame::addPlayer() {
    if ((int)players.size()!= max_players) {
        ConnectionId id = this->new_connection_id;
        players.push_back(id);
        if ((int)players.size() == max_players){
            first_iteration = true;
        }
        ++(this->new_connection_id);
        return id;
    }
    return 0;
    //MANDAR MENSAJE PARTIDA LLENA
}

void PreGame::deletePlayer(const ConnectionId id) {
    if ((int)players.size() == max_players) {
        game.deletePlayer(id);
    }
}