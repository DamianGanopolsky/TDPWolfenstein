#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "Panel_window.h"
#include "Player.h"
#include "Player_info.h"
#include "Map_2d.h"
#include "Ray.h"
#include "Constant_rate_loop.h"

#include <SDL2/SDL.h>

class Client {
public:
    void update();

    void render();

    Client(Panel_window& Panel,Player& Player,Map_2d& Map);

    Player get_player();

private: 
    Panel_window& panel;
    Player& player;
    Map_2d& map;
    //Constant_rate_loop crl;
    std::set<Ray> rays;
    std::list<Game_element> elements;
	
};

#endif