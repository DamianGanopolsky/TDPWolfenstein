#ifndef MAP_H_
#define MAP_H_

#include "../player/player.h"
#include "./../commands/command_manager.h"
#include <unordered_map>


class Map {
 public:
    Map(int width, int height);
    //cargar_mapa(char* archivo_yalm)
    // update()
    // send
    // recieve
    void update_player(int command, int player_id);

 private:
    std::unordered_map<int, Player> players;
    int** map;
    CommandManager cmd;
    
};

#endif   // MAP_H_
