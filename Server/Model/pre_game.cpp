#include "./pre_game.h"

#define PATH_TO_MAP "../Maps/"
#define YAML_EXT ".yaml"

PreGame::PreGame(ClientsConnected& clients_connected, std::string map_Yaml, int& rate) :  
                    new_connection_id(1),
                    players(0), game_started(false),
                    game(clients_connected, map_Yaml, rate) {
                        YAML::Node config = YAML::LoadFile(PATH_TO_MAP+map_Yaml+YAML_EXT);
                        this->max_players = config["Map"]["Cant_players"].as<int>();
                    }

PreGame::~PreGame() {}

bool PreGame::update(int iteration) {
    if (players == max_players){
        game.updatePlayers(iteration);
        game_started = true;
        return true;
    }
    return false;
}

ConnectionId PreGame::addPlayer(std::string& nickname) {
    if (players != max_players) {
        ConnectionId id = this->new_connection_id;
        this->game.newPlayer(id, nickname);
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
    } else if (!game_started) {
        --(this->players);
        --(this->new_connection_id);
    }
}