#include "player/player.h"
#include "player/player_info.h"
#include "actions/interact.h"
#include "position/position_player.h"
#include "config.h"

#include "objects/items/bullets/bullet.h"
#include "objects/items/healers/kit.h"

int main(int argc, char* argv[]) {
    PlayerInfo player_info;
    Player player(player_info);
    Interact interacter(player_info);
    Position pos(PLAYER_INITIAL_POS_X, PLAYER_INITIAL_POS_Y, MAP_WIDTH, MAP_HEIGHT);

    Bullet bullet;
    int goThoughBullet = interacter.interactWith(bullet);

    Kit kit;
    int goThoughKit = interacter.interactWith(kit);

    return 0;
}
