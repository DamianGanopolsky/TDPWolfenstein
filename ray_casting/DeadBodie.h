#ifndef __DEADBODIE_H__
#define __DEADBODIE_H__

#include <SDL2/SDL.h>
#include "panel_status/Element_panel_status.h"
#include "const.h"

class DeadBodie {
public:
    DeadBodie(int Type_Player,int x,int y,SDL_Renderer*& Renderer);

    void copy_to_renderer();

private: 
    int type_player;
    int pos_x;
    int pos_y;
    SDL_Renderer* renderer;
    int status;
    Element_panel_status officer_dead_status;
	Element_panel_status eguard_dead_status;
	Element_panel_status guard_dead_status;
};

#endif