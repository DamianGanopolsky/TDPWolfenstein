#include "Map.h"
#include <iostream>
#define FLOOR_TILE 0
#define TREASURE 1
#define PLAYER 2
#define X_SIZE 36
#define Y_SIZE 21


int level1[36][21] = {
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1},
    { 1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1},
    { 1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1},
    { 1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1},
    { 1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

Map::Map(SdlWindow& Window):window(Window){
    
    camera.x=0;
    camera.y=0;
    SDL_Surface* tre_surface=IMG_Load("../Assets/Trophy.png");
    treasure=SDL_CreateTextureFromSurface(window.getRenderer(),tre_surface);
    SDL_Surface* player_surface = IMG_Load("../prueba_mapa/assets/imagen1.png");
    player=SDL_CreateTextureFromSurface(window.getRenderer(),player_surface);
    SDL_Surface* bar_surface=IMG_Load("../Editor/Barra2.png");
    bar=SDL_CreateTextureFromSurface(window.getRenderer(),bar_surface);
    SDL_Surface* floor_tile_surf=IMG_Load("../Editor/Barra2.png");
    floor_tile=SDL_CreateTextureFromSurface(window.getRenderer(),floor_tile_surf);
}

void Map::HandleMovementWASD(SDL_Event* event){
    switch(event->key.keysym.sym){
        case SDLK_w:
            camera.y=camera.y-1;
            break;
        case SDLK_a:
            camera.x=camera.x-1;
            break;
        case SDLK_s:
            camera.y=camera.y+1;
            break;
        case SDLK_d:
            camera.x=camera.x+1;
            break;
    }
}

void Map::draw(position initial_position,position draw_position){
    int block_frame=int(initial_position.x)/145;
    int matrix_x=(draw_position.x+camera.x*32)/32;
    int matrix_y=(draw_position.y+camera.y*32)/32;
    switch(block_frame){
        case 0:
            level1[matrix_x][matrix_y]=TREASURE;
            break;
        case 1:
            level1[matrix_x][matrix_y]=PLAYER;
            break;
        default:
            break;
    }
}

void Map::render(){
    int pos_x=0;
    int pos_y=0;
    for(int i=camera.x;i<camera.x+32;i++){
        for(int j=camera.y;j<camera.y+19;j++){
            if((i>X_SIZE)||(j>Y_SIZE)||(i<0)||(j<0)){
                pos_y++;
                continue;
            }
            SDL_Rect rect={pos_x*32,pos_y*32,32,32};
            pos_y++;

            switch(level1[i][j]){
                case FLOOR_TILE:
                    SDL_RenderCopy(window.getRenderer(),floor_tile,NULL,&rect);
                    break;
                case TREASURE:
                    SDL_RenderCopy(window.getRenderer(),floor_tile,NULL,&rect);
                    SDL_RenderCopy(window.getRenderer(),treasure,NULL,&rect);
                    break;
                case PLAYER:
                    SDL_RenderCopy(window.getRenderer(),floor_tile,NULL,&rect);
                    SDL_RenderCopy(window.getRenderer(),player,NULL,&rect);
                    break;
                default:
                    break;
            }
        }
        pos_y=0;
        pos_x++;
    }
}

Map::~Map(){

}