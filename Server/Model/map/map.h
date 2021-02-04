#ifndef MAP_H_
#define MAP_H_

#include "../player/player.h"
#include <unordered_map>
#include "../../../Editor/YamlParser.h"


class Map {
 public:
   // Map(int width, int height);
    Map(std::string YamlPathToMap);
    ~Map();
    //cargar_mapa(char* archivo_yalm)
    // update()
    // send
    // recieve
    //void update_player(int command, Id player_id, Id target_id);

 private:
    std::unordered_map<Id, Player> players;
    int** map;
    int rows;
    int columns;

    void LoadMatrix(std::map <std::pair<int,int>,int> initial_map);
    
};

#endif   // MAP_H_
