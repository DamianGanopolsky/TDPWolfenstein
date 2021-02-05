#include "map.h"
#include "../constants/const_object_map.h"
#define CUADRICULA 64

Map::Map(std::string YamlPathToMap){
    YamlParser yamlparser(YamlPathToMap);
    std::map <std::pair<int,int>,int> initial_map =yamlparser.load_map(YamlPathToMap);
    rows=yamlparser.Map_Height();
    columns=yamlparser.Map_Width();
    _loadMatrix(initial_map);
}

//HACERLE FREE A LA MATRIZ
Map::~Map() {}

void Map::_loadMatrix(std::map <std::pair<int,int>,int> initial_map){
    map= new int*[rows];
    for(int i = 0; i < rows; ++i){
        map[i] = new int[columns];
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            map[i][j]=MAP_NONE;
        }
    }
    for (auto const& x : initial_map){
        if(x.second==MAP_PLAYER_EDITOR){
            continue;
        }
        map[x.first.first/CUADRICULA][x.first.second/CUADRICULA]=x.second;
    }
}

int Map::getObjectPos(int x, int y) {
    int cell_x = (x/POINTS_PER_CELL);
    int cell_y = (y/POINTS_PER_CELL);
    return map[cell_x][cell_y];
}

void Map::setObjectPos(int x, int y, ObjectsInMap object) {
    int cell_x = (x/POINTS_PER_CELL);
    int cell_y = (y/POINTS_PER_CELL);
    map[cell_x][cell_y] = object;
}

/*void Map::update_player(int command, Id player_id, Id target_id) {
    Player player = this->players[player_id];
    Player target = this->players[target_id];
    cmd.applyCommand(command, this->map, player, target);
}*/