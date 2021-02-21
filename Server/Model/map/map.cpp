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

Map::~Map() {
    for(int i=0;i<columns;i++){
        delete [] map[i];
    }
    delete[] map;
}

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
    /*
    MAP_CHAIN_CANNON    = 256,
    MAP_GUN             = 512,
    MAP_MACHINE_GUN     = 1024,
    MAP_KNIFE 
    */
    for (auto const& x : initial_map){
        //std::cout << "En x:" << x.first.first << "en y:" << x.first.second << "obj:" << x.second << std::endl;
        if(x.second==MAP_KNIFE){
            std::cout << "Hay chain cannon en x:" << x.first.first <<"y:" << x.first.second << std::endl;
            std::cout << "Hay chain cannon en cuadricula x:" << x.first.first/CUADRICULA <<"y:" << x.first.second/CUADRICULA << std::endl;
        }
        if(x.second==MAP_GUN){
            std::cout << "Hay chain cannon en x:" << x.first.first <<"y:" << x.first.second << std::endl;
            std::cout << "Hay chain cannon en cuadricula x:" << x.first.first/CUADRICULA <<"y:" << x.first.second/CUADRICULA << std::endl;
        }
        if(x.second==MAP_MACHINE_GUN){
            std::cout << "Hay chain cannon en x:" << x.first.first <<"y:" << x.first.second << std::endl;
            std::cout << "Hay chain cannon en cuadricula x:" << x.first.first/CUADRICULA <<"y:" << x.first.second/CUADRICULA << std::endl;
        }
        if(x.second==MAP_CHAIN_CANNON){
            std::cout << "Hay chain cannon en x:" << x.first.first <<"y:" << x.first.second << std::endl;
            std::cout << "Hay chain cannon en cuadricula x:" << x.first.first/CUADRICULA <<"y:" << x.first.second/CUADRICULA << std::endl;
        }
        if(x.second==MAP_PLAYER){
            continue;
        }

        map[x.first.first/CUADRICULA][x.first.second/CUADRICULA]=x.second;
    }
}

int Map::getObjectPos(int x, int y) {
    int cell_x = (x/POINTS_PER_CELL);
    int cell_y = (y/POINTS_PER_CELL);
    std::cout << "cell: " << cell_x << ", " << cell_y << std::endl;
    return map[cell_x][cell_y];
}

void Map::setObjectPos(int x, int y, ObjectsInMap object) {
    int cell_x = (x/POINTS_PER_CELL);
    int cell_y = (y/POINTS_PER_CELL);
    map[cell_x][cell_y] = object;
}

std::pair<int, int> Map::getNextPos(Direction direction, int x ,int y, int value) {
    switch (direction) {
        /*
    int new_y = (this->y + 1 > this->height) ? this->height : (this->y + 1);
        */
        case UP_DIR: {
            int new_x = (x/POINTS_PER_CELL);
            int new_y = ((y/POINTS_PER_CELL)+value > this->rows) ? this->rows : (y/POINTS_PER_CELL)+value;
            return std::pair<int, int> (new_x, new_y);
        }
        case DOWN_DIR: {
            int new_x = (x/POINTS_PER_CELL);
            int new_y = ((y/POINTS_PER_CELL)-value < 0) ? 0 : (y/POINTS_PER_CELL)-value;
            return std::pair<int, int> (new_x, new_y);
        }
        case LEFT_DIR: {
            int new_x = ((x/POINTS_PER_CELL)+value > this->columns) ? this->columns : (x/POINTS_PER_CELL)+value;
            int new_y = (y/POINTS_PER_CELL);
            return std::pair<int, int> (new_x, new_y);
        }
        case RIGHT_DIR: {
            int new_x = ((x/POINTS_PER_CELL)-value < 0) ? 0 : (x/POINTS_PER_CELL);
            int new_y = (y/POINTS_PER_CELL);
            return std::pair<int, int> (new_x, new_y);
        }
        default: {
            throw Exception("Unknown next position");
            break;
        }
    }
    return std::pair<int, int> (-1, -1);
}