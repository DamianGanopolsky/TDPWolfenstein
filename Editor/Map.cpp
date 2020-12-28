#include "Map.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "../Editor/SdlClasses/SdlText.h"

#define FLOOR_TILE 0
#define PLAYER 1
#define TREASURE 2
#define MEDICAL_KIT 3
#define KEY 4
#define AUTOMATIC_GUN 5
#define CHAIN_CANON 6
#define FOOD 7
#define BULLETS 8
#define WALL 9
#define DOOR 10
#define X_SIZE 36
#define Y_SIZE 21
#define TILE_PIXELS 32
#define SCREEN_HEIGTH 19
#define SCREEN_WIDTH 32
#define BUCKET_BAR_SPACE 145
#define TOTAL_IMAGES 17


int level1[36][21] = {
    { 0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,9,9,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,0},
    { 0,9,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0},
    { 0,9,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0},
    { 0,9,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0},
    { 0,10,0,0,0,2,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0},
    { 0,9,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0},
    { 0,9,0,0,0,0,0,0,0,0,3,3,0,9,0,0,0,0,0,0,0},
    { 0,9,0,0,0,0,0,0,0,0,3,3,0,9,0,0,0,0,0,0,0},
    { 0,9,9,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

void Map::printMatrix(){
    std::cout << matrix[rows-1][columns-1] << std::endl;
}

void Map::LoadMatrix(){
    rows=36;
    columns=21;
    matrix= new int*[rows];
    for(int i = 0; i < rows; ++i){
        matrix[i] = new int[columns];
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            matrix[i][j]=level1[i][j];
        }
    }
    std::cout << matrix[0][0] << std::endl;
}

void Map::ExpandMap(){
    int** aux = new int*[rows];
    for(int i = 0; i < rows; ++i){
        aux[i] = new int[columns];
    }
    int previous_rows=rows;
    int previous_cols=columns;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            aux[i][j]=matrix[i][j];
        }
    }
    for(int i=0;i<rows;i++){
        delete matrix[i];
    }
    delete matrix;
    rows=rows+5;
    columns=columns+5;
    matrix=new int*[rows];
    for(int i=0;i<rows;i++){
        matrix[i]=new int[columns];
    }
    for(int i=0;i<previous_rows;i++){
        for(int j=0;j<previous_cols;j++){
            matrix[i][j]=aux[i][j];
        }
    }
    for(int i=0;i<previous_rows;i++){
        delete aux[i];
    }
    delete aux;
    matrix[rows-1][columns-1]=14;
}


Map::Map(SdlWindow& Window):window(Window),player_count(0){
    camera.x=0;
    camera.y=0;
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/GreyTile.png"));
    surfaces.push_back(IMG_Load("../prueba_mapa/assets/imagen1.png"));
    surfaces.push_back(IMG_Load("../Assets/Trophy.png"));
    surfaces.push_back(IMG_Load("../Assets/MedicalKit.png"));
    surfaces.push_back(IMG_Load("../Assets/Key.png"));
    surfaces.push_back(IMG_Load("../Assets/Ametralladora.png"));
    surfaces.push_back(IMG_Load("../Assets/CanionDeCadena.png"));
    surfaces.push_back(IMG_Load("../Assets/Food.png"));
    surfaces.push_back(IMG_Load("../Assets/BulletsOriginal.png"));
    surfaces.push_back(IMG_Load("../Assets/Wall.png"));
    surfaces.push_back(IMG_Load("../Assets/Door.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Player_Number/Uno.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Player_Number/Dos.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Player_Number/Tres.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Player_Number/Cuatro.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Player_Number/Cinco.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Player_Number/Seis.png"));
    for(int i=0;i<TOTAL_IMAGES;i++){
        textures.push_back(SDL_CreateTextureFromSurface(window.getRenderer(),surfaces.at(i)));
    }
    LoadMatrix();
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
    int matrix_x=(draw_position.x+camera.x*TILE_PIXELS)/TILE_PIXELS;
    int matrix_y=(draw_position.y+camera.y*TILE_PIXELS)/TILE_PIXELS;
    if(initial_position.y<0.815625*window.getHeight()){
        return;
    }
    if((initial_position.x>=(0.052*window.getWidth()))&&(initial_position.x<=0.1885*window.getWidth())){
        if(matrix[matrix_x][matrix_y]!=PLAYER){
            player_count++;
            std::pair<int,int> pair_key;
            pair_key.first=matrix_x;
            pair_key.second=matrix_y;
            player_map.insert({pair_key,player_count});
        }
        matrix[matrix_x][matrix_y]=PLAYER;
        
    }
    else if((initial_position.x>=(0.2312*window.getWidth()))&&(initial_position.x<=0.2885*window.getWidth())){
        matrix[matrix_x][matrix_y]=TREASURE;
    }
    else if((initial_position.x>=(0.2958*window.getWidth()))&&(initial_position.x<=0.3489*window.getWidth())){
        matrix[matrix_x][matrix_y]=MEDICAL_KIT;
    }
    else if((initial_position.x>=(0.3552*window.getWidth()))&&(initial_position.x<=0.4125*window.getWidth())){
        matrix[matrix_x][matrix_y]=KEY;
    }
    else if((initial_position.x>=(0.4187*window.getWidth()))&&(initial_position.x<=0.4770*window.getWidth())){
        matrix[matrix_x][matrix_y]=AUTOMATIC_GUN;
    }
    else if((initial_position.x>=(0.4833*window.getWidth()))&&(initial_position.x<=0.5364*window.getWidth())){
        matrix[matrix_x][matrix_y]=CHAIN_CANON;
    }
    else if((initial_position.x>=(0.5416*window.getWidth()))&&(initial_position.x<=0.5979*window.getWidth())){
        matrix[matrix_x][matrix_y]=FOOD;
    }
    else if((initial_position.x>=(0.6041*window.getWidth()))&&(initial_position.x<=0.6666*window.getWidth())){
        matrix[matrix_x][matrix_y]=BULLETS;
    }
    else if((initial_position.x>=(0.7218*window.getWidth()))&&(initial_position.x<=0.8041*window.getWidth())){
        if(matrix[matrix_x][matrix_y]==PLAYER){
            player_count--;
        }
        matrix[matrix_x][matrix_y]=FLOOR_TILE;
    }
    else if((initial_position.x>=(0.8093*window.getWidth()))&&(initial_position.x<=0.8854*window.getWidth())){
        matrix[matrix_x][matrix_y]=WALL;
    }
    else if((initial_position.x>=(0.8916*window.getWidth()))&&(initial_position.x<=0.9687*window.getWidth())){
        matrix[matrix_x][matrix_y]=DOOR;
    }
}

void Map::render(){
    int pos_x=0;
    int pos_y=0;
    std::pair<int,int> key;
    int player_number;
    for(int i=camera.x;i<camera.x+SCREEN_WIDTH;i++){
        for(int j=camera.y;j<camera.y+SCREEN_HEIGTH;j++){
            if((i>=X_SIZE)||(j>=Y_SIZE)||(i<0)||(j<0)){
                pos_y++;
                continue;
            }
            SDL_Rect rect={pos_x*TILE_PIXELS,pos_y*TILE_PIXELS,TILE_PIXELS,TILE_PIXELS};
            SDL_Rect rect_text={pos_x*TILE_PIXELS+3,(pos_y*TILE_PIXELS)-10,TILE_PIXELS,TILE_PIXELS};
            pos_y++;
            SDL_RenderCopy(window.getRenderer(),textures.at(0),NULL,&rect);
            switch(matrix[i][j]){
                case FLOOR_TILE:
                    break;
                case PLAYER:
                    key.first=(pos_x*TILE_PIXELS+camera.x*TILE_PIXELS)/TILE_PIXELS;
                    key.second=((pos_y*TILE_PIXELS+camera.y*TILE_PIXELS)/TILE_PIXELS)-1;
                    player_number=player_map.at(key);
                    SDL_RenderCopy(window.getRenderer(),textures.at(1),NULL,&rect);
                    switch(player_number){
                        case 1:
                            SDL_RenderCopy(window.getRenderer(), textures.at(11), NULL, &rect_text); 
                            break;
                        case 2:
                            SDL_RenderCopy(window.getRenderer(), textures.at(12), NULL, &rect_text); 
                            break;
                        case 3:
                            SDL_RenderCopy(window.getRenderer(), textures.at(13), NULL, &rect_text); 
                            break;
                        case 4:
                            SDL_RenderCopy(window.getRenderer(), textures.at(14), NULL, &rect_text); 
                            break;
                        case 5:
                            SDL_RenderCopy(window.getRenderer(), textures.at(15), NULL, &rect_text); 
                            break;
                        case 6:
                            SDL_RenderCopy(window.getRenderer(), textures.at(16), NULL, &rect_text); 
                            break;
                    }
                    break;
                case TREASURE:
                    SDL_RenderCopy(window.getRenderer(),textures.at(2),NULL,&rect);
                    break;

                case MEDICAL_KIT:
                    SDL_RenderCopy(window.getRenderer(),textures.at(3),NULL,&rect);
                    break;
                case KEY:
                    SDL_RenderCopy(window.getRenderer(),textures.at(4),NULL,&rect);
                    break;
                case AUTOMATIC_GUN:
                    SDL_RenderCopy(window.getRenderer(),textures.at(5),NULL,&rect);
                    break;
                case CHAIN_CANON:
                    SDL_RenderCopy(window.getRenderer(),textures.at(6),NULL,&rect);
                    break;
                case FOOD:
                    SDL_RenderCopy(window.getRenderer(),textures.at(7),NULL,&rect);
                    break;
                case BULLETS:
                    SDL_RenderCopy(window.getRenderer(),textures.at(8),NULL,&rect);
                    break;
                case WALL:
                    SDL_RenderCopy(window.getRenderer(),textures.at(9),NULL,&rect);
                    break;
                case DOOR:
                    SDL_RenderCopy(window.getRenderer(),textures.at(10),NULL,&rect);
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
    for(int i=0;i<rows;i++){
        delete matrix[i];
    }
    delete matrix;
}