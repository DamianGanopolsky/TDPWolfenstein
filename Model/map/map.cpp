#include "map.h"

Map::Map(int width, int height) {
    int map[width][height];
    *this->map = *map;
}

void Map::update_player(int command, int player_id) {
    Player player1 = this->players[player_id];
    cmd.applyCommand(command, this->map, player1);
}
