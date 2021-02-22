#include "Map.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "../Editor/SdlClasses/SdlText.h"
#include "YamlParser.h"
#include "../Server/Model/constants/const_object_map.h"

#define TILE_PIXELS 32
#define SCREEN_HEIGTH 50
#define SCREEN_WIDTH 50
#define TOTAL_IMAGES 17
#define CUADRICULA 64

void Map::LoadMatrix(std::map <std::pair<int,int>,int> initial_map){
    matrix= new int*[rows];
    for(int i = 0; i < rows; ++i){
        matrix[i] = new int[columns];
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            matrix[i][j]=MAP_NONE;
        }
    }
    for (auto const& x : initial_map){
        matrix[x.first.first/CUADRICULA][x.first.second/CUADRICULA]=x.second;
        if(x.second==MAP_PLAYER){
            player_count++;
            std::pair<int,int> pair_key;
            pair_key.first=x.first.first/CUADRICULA;
            pair_key.second=x.first.second/CUADRICULA;
            player_map.insert({pair_key,player_count});
        }
    }

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
    rows=rows+1;
    columns=columns+1;
    matrix=new int*[rows];
    for(int i=0;i<rows;i++){
        matrix[i]=new int[columns];
    }
    for(int i=0;i<previous_rows;i++){
        for(int j=0;j<previous_cols;j++){
            matrix[i][j]=aux[i][j];
        }
    }
    for(int i=0;i<rows;i++){
        for(int j=previous_cols;j<columns;j++){
            matrix[i][j]=MAP_NONE;
        }
    }
    for(int i=previous_rows;i<rows;i++){
        for(int j=0;j<columns;j++){
            matrix[i][j]=MAP_NONE;
        }
    }
    for(int i=0;i<previous_rows;i++){
        delete aux[i];
    }
    delete aux;
}

void Map::ShrinkMap(){
    rows=rows-1;
    columns=columns-1;
}

void Map::printMap(){
    /*for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            std::cout << "En x:" << i << "En y:" << j <<  "  Objeto:" << matrix[i][j] << std::endl;
        }
    }*/
}


Map::Map(SdlWindow& Window,std::string YamlPath):window(Window),player_count(0){
    YAML::Node config = YAML::LoadFile("../Yaml_configs/editor_config.yaml");
    //int total_images = config["total_images_to_load"].as<int>();
    //cuadricula=config["cuadricula_size"].as<int>();
    camera.x=0;
    camera.y=0;
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/GreyTile.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/imagen1.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Trophy.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/MedicalKit.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Key.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Ametralladora.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/CanionDeCadena.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets//Food.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/BulletsOriginal.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Wall.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Door.png"));

    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Player_Number/Uno.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Player_Number/Dos.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Player_Number/Tres.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Player_Number/Cuatro.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Player_Number/Cinco.png"));
    surfaces.push_back(IMG_Load("../Editor/Editor_Assets/Player_Number/Seis.png"));
    for(int i=0;i<TOTAL_IMAGES;i++){
        textures.push_back(SDL_CreateTextureFromSurface(window.getRenderer(),surfaces.at(i)));
    }
}

void Map::LoadMap(std::string YamlPath){
    YamlParser yamlparser(YamlPath);
    std::map <std::pair<int,int>,int> initial_map =yamlparser.load_map(YamlPath);
    rows=yamlparser.Map_Height();
    columns=yamlparser.Map_Width();
    LoadMatrix(initial_map);
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

void Map::click(position final_pos){
    if((final_pos.y>0.8578*window.getHeight())&&(final_pos.y<0.9406*window.getHeight())){
        if((final_pos.x>=(0.7719*window.getWidth()))&&(final_pos.x<=0.8760*window.getWidth())){
            ExpandMap();
        }
        else if((final_pos.x>=(0.8833*window.getWidth()))&&(final_pos.x<=0.9896*window.getWidth())){
            ShrinkMap();
        }
    }
}

void Map::draw(position initial_position,position draw_position){
    int matrix_x=(draw_position.x+camera.x*TILE_PIXELS)/TILE_PIXELS;
    int matrix_y=(draw_position.y+camera.y*TILE_PIXELS)/TILE_PIXELS;
    if((matrix_x>=rows)||(matrix_y>=columns)){
        return;
    }
    if(initial_position.y<0.815625*window.getHeight()){
        return;
    }
    if((initial_position.x>=(0.0073*window.getWidth()))&&(initial_position.x<=0.1292*window.getWidth())){
        if(matrix[matrix_x][matrix_y]!=MAP_PLAYER){
            player_count++;
            std::pair<int,int> pair_key;
            pair_key.first=matrix_x;
            pair_key.second=matrix_y;
            player_map.insert({pair_key,player_count});
        }
        matrix[matrix_x][matrix_y]=MAP_PLAYER;
        
    }
    else if((initial_position.x>=(0.1396*window.getWidth()))&&(initial_position.x<=0.1906*window.getWidth())){
        matrix[matrix_x][matrix_y]=MAP_CUP;
    }
    else if((initial_position.x>=(0.1979*window.getWidth()))&&(initial_position.x<=0.2469*window.getWidth())){
        matrix[matrix_x][matrix_y]=MAP_KIT;
    }
    else if((initial_position.x>=(0.2531*window.getWidth()))&&(initial_position.x<=0.3042*window.getWidth())){
        matrix[matrix_x][matrix_y]=MAP_KEY;
    }
    else if((initial_position.x>=(0.3094*window.getWidth()))&&(initial_position.x<=0.3604*window.getWidth())){
        matrix[matrix_x][matrix_y]=MAP_MACHINE_GUN;
    }
    else if((initial_position.x>=(0.3656*window.getWidth()))&&(initial_position.x<=0.4135*window.getWidth())){
        matrix[matrix_x][matrix_y]=MAP_CHAIN_CANNON;
    }
    else if((initial_position.x>=(0.4198*window.getWidth()))&&(initial_position.x<=0.4677*window.getWidth())){
        matrix[matrix_x][matrix_y]=MAP_FOOD;
    }
    else if((initial_position.x>=(0.474*window.getWidth()))&&(initial_position.x<=0.5271*window.getWidth())){
        matrix[matrix_x][matrix_y]=MAP_BULLET;
    }
    else if((initial_position.x>=(0.5385*window.getWidth()))&&(initial_position.x<=0.6093*window.getWidth())){
        if(matrix[matrix_x][matrix_y]==MAP_PLAYER){
            player_count--;
        }
        matrix[matrix_x][matrix_y]=MAP_NONE;
    }
    else if((initial_position.x>=(0.6177*window.getWidth()))&&(initial_position.x<=0.6833*window.getWidth())){
        matrix[matrix_x][matrix_y]=MAP_WALL;
    }
    else if((initial_position.x>=(0.6906*window.getWidth()))&&(initial_position.x<=0.7583*window.getWidth())){
        matrix[matrix_x][matrix_y]=MAP_LOCKED_DOOR;
    }

}

void Map::render(){
    int pos_x=0;
    int pos_y=0;
    std::pair<int,int> key;
    int player_number;
    
    for(int i=camera.x;i<camera.x+SCREEN_WIDTH;i++){
        for(int j=camera.y;j<camera.y+SCREEN_HEIGTH;j++){
            if((i>=rows)||(j>=columns)||(i<0)||(j<0)){
                pos_y++;
                continue;
            }
            SDL_Rect rect={pos_x*TILE_PIXELS,pos_y*TILE_PIXELS,TILE_PIXELS,TILE_PIXELS};
            //SDL_Rect rect_text={pos_x*TILE_PIXELS+3,(pos_y*TILE_PIXELS)-10,TILE_PIXELS,TILE_PIXELS};
            SDL_Rect rect_text={pos_x*TILE_PIXELS+10,(pos_y*TILE_PIXELS)-5,TILE_PIXELS/2,TILE_PIXELS/2};
            pos_y++;
            SDL_RenderCopy(window.getRenderer(),textures.at(0),NULL,&rect);
            switch(matrix[i][j]){
                case MAP_NONE:
                    break;
                case MAP_PLAYER:
                {
                    
                    key.first=(pos_x*TILE_PIXELS+camera.x*TILE_PIXELS)/TILE_PIXELS;
                    key.second=((pos_y*TILE_PIXELS+camera.y*TILE_PIXELS)/TILE_PIXELS)-1;
                    player_number=player_map.at(key);
                    SDL_RenderCopy(window.getRenderer(),textures.at(1),NULL,&rect);
                    std::string lives_str=std::to_string(player_number);
                    TTF_Font* Sans = TTF_OpenFont("../client/panel_status/OpenSans-Bold.ttf", 20); 
                    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, lives_str.c_str(), {152, 0, 2});
                    SDL_Texture* texture_of_text = SDL_CreateTextureFromSurface(window.getRenderer(),surfaceMessage); 
                    SDL_RenderCopy(window.getRenderer(), texture_of_text, NULL, &rect_text);
                    SDL_FreeSurface(surfaceMessage);
                    SDL_DestroyTexture(texture_of_text);
                    TTF_CloseFont(Sans);
                }
                    break;
                case MAP_CUP:
                    SDL_RenderCopy(window.getRenderer(),textures.at(2),NULL,&rect);
                    break;
                case MAP_KIT:
                    SDL_RenderCopy(window.getRenderer(),textures.at(3),NULL,&rect);
                    break;
                case MAP_KEY:
                    SDL_RenderCopy(window.getRenderer(),textures.at(4),NULL,&rect);
                    break;
                case MAP_MACHINE_GUN:
                    SDL_RenderCopy(window.getRenderer(),textures.at(5),NULL,&rect);
                    break;
                case MAP_CHAIN_CANNON:
                    SDL_RenderCopy(window.getRenderer(),textures.at(6),NULL,&rect);
                    break;
                case MAP_FOOD:
                    SDL_RenderCopy(window.getRenderer(),textures.at(7),NULL,&rect);
                    break;
                case MAP_BULLET:
                    SDL_RenderCopy(window.getRenderer(),textures.at(8),NULL,&rect);
                    break;
                case MAP_WALL:
                    SDL_RenderCopy(window.getRenderer(),textures.at(9),NULL,&rect);
                    break;
                case MAP_LOCKED_DOOR:
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

void Map::Export(std::string yamlName){
    std::map <int,std::vector<std::pair<int,int>>> player_map;
    std::pair<int,int> position;
    for(int i=0;i<rows;i++){

        for(int j=0;j<columns;j++){
            if(matrix[i][j]==0) continue;

            position = std::make_pair (i,j);
            player_map[matrix[i][j]].push_back(position);
        }
    }
    YamlParser yamlparser(yamlName);
    yamlparser.Write_Map(yamlName,player_map,rows,columns);
}

Map::~Map(){
    /*for(int i=0;i<rows;i++){
        delete matrix[i];
    }
    delete matrix;*/
}