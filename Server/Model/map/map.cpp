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
    for (auto const& x : initial_map){
        if(x.second==MAP_PLAYER){
            continue;
        }

        map[x.first.first/CUADRICULA][x.first.second/CUADRICULA]=x.second;
    }
}

int Map::getObjectPos(int x, int y) {
    int cell_x = (x/GameConfig.points_per_cell);
    int cell_y = (y/GameConfig.points_per_cell);
    std::cout << "cell: " << cell_x << ", " << cell_y << std::endl;
    return map[cell_x][cell_y];
}

void Map::setObjectPos(int x, int y, ObjectsInMap object) {
    int cell_x = (x/GameConfig.points_per_cell);
    int cell_y = (y/GameConfig.points_per_cell);
    map[cell_x][cell_y] = object;
}

std::pair<int, int> Map::getNextPos(Direction direction, int x ,int y, int value) {
    switch (direction) {
        /*
    int new_y = (this->y + 1 > this->height) ? this->height : (this->y + 1);
        */
        case UP_DIR: {
            int new_x = (x/GameConfig.points_per_cell);
            int new_y = ((y/GameConfig.points_per_cell)+value > this->rows) ? this->rows : (y/GameConfig.points_per_cell)+value;
            return std::pair<int, int> (new_x, new_y);
        }
        case DOWN_DIR: {
            int new_x = (x/GameConfig.points_per_cell);
            int new_y = ((y/GameConfig.points_per_cell)-value < 0) ? 0 : (y/GameConfig.points_per_cell)-value;
            return std::pair<int, int> (new_x, new_y);
        }
        case LEFT_DIR: {
            int new_x = ((x/GameConfig.points_per_cell)+value > this->columns) ? this->columns : (x/GameConfig.points_per_cell)+value;
            int new_y = (y/GameConfig.points_per_cell);
            return std::pair<int, int> (new_x, new_y);
        }
        case RIGHT_DIR: {
            int new_x = ((x/GameConfig.points_per_cell)-value < 0) ? 0 : (x/GameConfig.points_per_cell);
            int new_y = (y/GameConfig.points_per_cell);
            return std::pair<int, int> (new_x, new_y);
        }
        default: {
            throw Exception("Unknown next position");
            break;
        }
    }
    return std::pair<int, int> (-1, -1);
}