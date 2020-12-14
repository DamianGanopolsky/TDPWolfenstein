#include "Map.h"
#include <iostream>
#define FLOOR_TILE 0
#define TREASURE 1
#define PLAYER 2
#define MEDICAL_KIT 3
#define BULLETS 4
#define DOOR 5
#define WALL 6
#define X_SIZE 36
#define Y_SIZE 21
#define TILE_PIXELS 32
#define SCREEN_HEIGTH 19
#define SCREEN_WIDTH 32
#define BUCKET_BAR_SPACE 145


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
    surfaces.push_back(IMG_Load("../Assets/Trophy.png"));
    surfaces.push_back(IMG_Load("../prueba_mapa/assets/imagen1.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Barra2.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/GreyTile.png"));
    surfaces.push_back(IMG_Load("../Assets/MedicalKit.png"));
    surfaces.push_back(IMG_Load("../Assets/BulletsOriginal.png"));
    surfaces.push_back(IMG_Load("../Assets/Door.png"));
    surfaces.push_back(IMG_Load("../Assets/Wall.png"));
    for(int i=0;i<8;i++){
        textures.push_back(SDL_CreateTextureFromSurface(window.getRenderer(),surfaces.at(i)));
    }
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
    int block_frame=int(initial_position.x)/BUCKET_BAR_SPACE;
    int matrix_x=(draw_position.x+camera.x*TILE_PIXELS)/TILE_PIXELS;
    int matrix_y=(draw_position.y+camera.y*TILE_PIXELS)/TILE_PIXELS;
    switch(block_frame){
        case 0:
            level1[matrix_x][matrix_y]=TREASURE;
            break;
        case 1:
            level1[matrix_x][matrix_y]=PLAYER;
            break;
        case 2:
            level1[matrix_x][matrix_y]=MEDICAL_KIT;
            break;
        case 3:
            level1[matrix_x][matrix_y]=BULLETS;
            break;
        case 4:
            level1[matrix_x][matrix_y]=DOOR;
            break;
        case 5:
            level1[matrix_x][matrix_y]=WALL;
            break;
        default:
            break;
    }
}

void Map::render(){
    int pos_x=0;
    int pos_y=0;
    for(int i=camera.x;i<camera.x+SCREEN_WIDTH;i++){
        for(int j=camera.y;j<camera.y+SCREEN_HEIGTH;j++){
            if((i>X_SIZE)||(j>Y_SIZE)||(i<0)||(j<0)){
                pos_y++;
                continue;
            }
            SDL_Rect rect={pos_x*TILE_PIXELS,pos_y*TILE_PIXELS,TILE_PIXELS,TILE_PIXELS};
            pos_y++;
            //SDL_RenderCopy(window.getRenderer(),floor_tile,NULL,&rect);
            SDL_RenderCopy(window.getRenderer(),textures.at(3),NULL,&rect);
            switch(level1[i][j]){
                case FLOOR_TILE:
                    break;
                case TREASURE:
                    //SDL_RenderCopy(window.getRenderer(),treasure,NULL,&rect);
                    SDL_RenderCopy(window.getRenderer(),textures.at(0),NULL,&rect);
                    break;
                case PLAYER:
                    SDL_RenderCopy(window.getRenderer(),textures.at(1),NULL,&rect);
                    //SDL_RenderCopy(window.getRenderer(),player,NULL,&rect);
                    break;
                case MEDICAL_KIT:
                    SDL_RenderCopy(window.getRenderer(),textures.at(4),NULL,&rect);
                    //SDL_RenderCopy(window.getRenderer(),medical_kit,NULL,&rect);
                    break;
                case BULLETS:
                    SDL_RenderCopy(window.getRenderer(),textures.at(0),NULL,&rect);
                    //SDL_RenderCopy(window.getRenderer(),bullets,NULL,&rect);
                    break;
                case DOOR:
                    SDL_RenderCopy(window.getRenderer(),textures.at(0),NULL,&rect);
                    //SDL_RenderCopy(window.getRenderer(),door,NULL,&rect);
                    break;
                case WALL:
                    SDL_RenderCopy(window.getRenderer(),textures.at(0),NULL,&rect);
                    //SDL_RenderCopy(window.getRenderer(),wall,NULL,&rect);
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