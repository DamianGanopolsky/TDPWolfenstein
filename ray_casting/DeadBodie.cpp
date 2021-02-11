#include "DeadBodie.h"

DeadBodie::DeadBodie(int Type_Player,int x,int y,SDL_Renderer*& Renderer):\
    type_player(Type_Player),pos_x(x),pos_y(y),renderer(Renderer),
    officer_dead_status(renderer,IMAGE_OFFICER_GUARDIAS_DEAD_PATH,TOTAL_OFFICER_GUARDIAS_DEAD),
										eguard_dead_status(renderer,IMAGE_EGUARDS_DEAD_PATH,TOTAL_EGUARDS_DEAD),
										guard_dead_status(renderer,IMAGE_DEATH_GUARDIAS_PATH,TOTAL_GUARDIAS_DEATH){
        status=2;
}

void DeadBodie::copy_to_renderer(){
    if(status>0){
        status= status -1;
    }
}