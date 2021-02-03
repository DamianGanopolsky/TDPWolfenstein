#include "map.h"

Map::Map(int width, int height) {
    int map[width][height];
    *this->map = *map;
}

Map::~Map() {}

/*void Map::update_player(int command, Id player_id, Id target_id) {
    Player player = this->players[player_id];
    Player target = this->players[target_id];
    cmd.applyCommand(command, this->map, player, target);
}*/
