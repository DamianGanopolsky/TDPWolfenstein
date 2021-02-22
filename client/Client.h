#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "Panel_window.h"
#include "Player.h"
#include "Player_info.h"
#include "Map_2d.h"
#include "Ray.h"
#include <vector>
#include "const.h"

#include <SDL2/SDL.h>

class Client {
public:
    void update();

    void render();

    Client(Panel_window& Panel,Player& Player,Map_2d& Map);

    void player_lost();

    void start_game();

    bool is_playing();

    void stop_game(std::vector<Player_stats> Final_Stats);

    Player get_player();

private: 
    Panel_window& panel;
    Player& player;
    Map_2d& map;
    //Constant_rate_loop crl;
    std::set<Ray> rays;
    std::list<Game_element> elements;
    bool player_lost_;
    bool game_finished;
	bool waiting_screen;
    std::vector<Player_stats> final_stats;
};

#endif