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
    void update_player(int command, Id player_id, Id target_id);

 private:
    std::unordered_map<Id, Player> players;
    int** map;
    CommandManager cmd;
    
};

#endif   // MAP_H_
